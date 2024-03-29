 SUBROUTINE resvp1(ndime,nnode,ndofn,nelem,ifpre,coora,euler,veloc,resid, &
                   emass,heade,dtime)
 !********************************************************************
 !
 !***   evaluation of constraints forces spot elements
 !
 !********************************************************************
 IMPLICIT NONE
 INTEGER (kind=4) ndime,nnode,ndofn,nelem,ifpre(:,:)
 REAL (kind=8) coora(:,:),euler(:,:),veloc(:),resid(:,:),emass(:,:),dtime
 TYPE(ele01), POINTER :: heade

 INTEGER (kind=4) ielem,isec,nl,osec,n1,n2,tc,rc,tcv,rcv,i,j,dir
 REAL (kind=8) x(ndime,nnode),bts(6),lx,dx(ndime),facto,lb(9,3),al(3), &
               v(6,3),stc,src,stcv,srcv,vx !,vr
 REAL (kind=8) xc(ndime,6), t(3,3), str(6), f(3,6), ft(3),long, a(3), b(3),lc(3,5)
 TYPE(ele01), POINTER :: e
 TYPE(section), POINTER :: sec
 LOGICAL :: newm,same
 TYPE (curve), POINTER :: c_tc, c_rc, c_tcv, c_rcv

 !INTEGER (kind=4) :: itera = 0                       !DEBUG
 !REAL (kind=8) :: fff(nelem),ddd(nelem)   !DEBUG

 !itera = itera + 1                                   !DEBUG
 !***  loop over all the elements
 osec = -1             !initializes
 nl = 3+ndime          !pointer to rotation values
 e => heade            !pointer to first element
 DO ielem = 1,nelem        !for each element
   isec  = e%matno         !associated section
   newm = isec /= osec     !compare with previous section
   IF ( newm )THEN            !if a different section
     sec => psecs(isec)%p                  !search and point
     osec = isec                           !keep section number
     IF( nnode == 2 )THEN
       tc  = sec%iprop(1)                  !curve for translational stiffnes
       rc  = sec%iprop(2)                  !curve for rotational stiffness
       tcv = sec%iprop(3)                  !curve for translational damping
       rcv = sec%iprop(4)                  !curve for rotational damping
       IF( tc  > 0 ) CALL cur_point( tc ,sec%mtbas%chead,c_tc )
       IF( rc  > 0 ) CALL cur_point( tc ,sec%mtbas%chead,c_rc )
       IF( tcv > 0 ) CALL cur_point( tcv,sec%mtbas%chead,c_tcv)
       IF( rcv > 0 ) CALL cur_point( rcv,sec%mtbas%chead,c_rcv)
       stc  = sec%rprop(1)                 !translational stiffnes
       src  = sec%rprop(2)                 !rotational stiffness
       stcv = sec%rprop(3)                 !translational damping
       srcv = sec%rprop(4)                 !rotational damping
       dir = sec%secdef(3)
     ELSE
       stc = sec%rprop(7)*sec%mtbas%prope(1) ! Area * Young
       src = sec%rprop(7)*sec%mtbas%prope(3) ! Area * Shear Modulus
       IF( dtime > 0d0 )THEN
         stcv = sec%rprop(7)/dtime**2        ! factor for contact constraint
       ELSE
         stcv = sec%rprop(7)*stc/3d0         ! factor for contact constraint
       END IF
     END IF
   END IF
   IF( nnode == 2 )THEN
     !       gathers the actual coordinates
     n1 = e%lnods(1)                 !first node
     n2 = e%lnods(2)                 !second node
     same = (n2 == 0)                !one node only
     ! Coordinates and velocities
     x(:,1) = coora(:,n1)            !coordinates of first node
     v = 0d0                         !initializes velocities
     DO i=1,ndofn                    !for each DOF
       j = ifpre(i,n1)                   !associated equation
       IF( j > 0 ) v(i,1) = veloc(j)     !non-prescribed velocity
     END DO
     IF( same ) THEN                 !if 1 node olny
       x(:,2) = e%gausv(2:ndime+1)    !recover original coordinates
     ELSE
       x(:,2) = coora(:,n2)           !coordinates of the second node
       DO i=1,ndofn                   !for each DOF
         j = ifpre(i,n2)                  !associated equation
         IF( j > 0 ) v(i,2) = veloc(j)    !non-prescribed velocity
       END DO
     END IF
     dx = x(:,2) - x(:,1)             !distance vector
     !ddd(ielem) = SQRT(DOT_PRODUCT(dx,dx))       !DEBUG
     SELECT CASE (dir)
     CASE( 1 )                  !X only
       dx(2:3) = 0d0
     CASE( 2 )                  !Y only
       dx(1:3:2) = 0d0
     CASE( 3 )                  !Z only
       dx(1:2) = 0d0
     CASE( 4 )                  !X-Y plane only
       dx(3) = 0d0
     CASE( 5 )                  !X-Z plane only
       dx(2) = 0d0
     CASE( 6 )                  !Y-Z plane only
       dx(1) = 0d0
     END SELECT
     lx = SQRT(DOT_PRODUCT(dx,dx))    !distance
     IF( lx > 0 )dx = dx/lx           !unit vector t (direction)
     v(:,3) = v(:,2) - v(:,1)         !velocity difference
     vx = DOT_PRODUCT(v(1:ndime,3),dx)  !proyection of velocity over direction t
     IF( tc  > 0 ) stc = inte_cr (c_tc%val,c_tc%np,lx,i)
     IF( tcv > 0 ) stcv= inte_cr (c_tcv%val,c_tcv%np,vx,i)
     facto = stc*lx + stcv*vx         !KT*e + CT*e' = force modulus
     bts(1:ndime) =  facto*dx         !force vector
     e%gausv(1) = facto               !keep present force modulus
     !fff(ielem) = facto           !DEBUG
     ! local system
     IF( e%rot )THEN                  !rotational stiffness or damping
       IF( ndime == 2 )THEN             !2-D
         al(1) = euler(1,n1)              !actual angle of 1st node
         IF( same ) THEN
           al(2) = e%gausv(nl)            !recover original angle
         ELSE
           al(2) = euler(1,n2)            !actual angle of second node
         END IF
         al(3) = al(2) - al(1)           !rotation
         IF( rc  > 0 ) src = inte_cr (c_rc%val,c_rc%np,al(3),i)
         IF( rcv > 0 ) srcv= inte_cr (c_rcv%val,c_rcv%np,v(3,3),i)
         facto = src*al(3) + srcv*v(3,3) !moment modulus
         bts(3) =  facto
       ELSE                             !3-D
         lb(:,1) = euler(:,n1)            !actual local system at first node
         IF( same ) THEN
           lb(:,2) = e%gausv(nl:nl+8)     !recover original system
         ELSE
           lb(:,2) = euler(:,n2)          !actual local system at second node
         END IF
         CALL proma4(lb(1,3),lb(1,1),lb(1,2),3,3,3) ! l3 = l1^T * l2
         CALL cuate8(lb(1,3),al(1))                 ! al = rotation vector
         lx = SQRT(DOT_PRODUCT(al,al))              ! rotation angle
         al = src*al + srcv*v(4:6,3)                ! moment vector
         facto = SQRT(DOT_PRODUCT(al,al))           ! moment modulus
         bts(4:6) =  al(1:3)                        !
       END IF
       IF( same )THEN
         e%gausv(2+ndime) = facto                   !keep moment modulus
       ELSE
         e%gausv(2) = facto                         !keep moment modulus
       END IF
     ELSE
       bts(ndime+1:ndofn) = 0d0                     !no contribution
     END IF

     resid(1:ndofn,n1) = resid(1:ndofn,n1) - bts(1:ndofn)   !sum to first node
     IF( .NOT.same ) &
       resid(1:ndofn,n2) = resid(1:ndofn,n2) + bts(1:ndofn) !sum to second node
   ELSE  !constraint between to triangles
     lc(1:2,1:5) = RESHAPE( e%gausv(1:10),(/2,5/) )
     lc(3,:) = 1d0 - lc(1,:) - lc(2,:)
     x = coora(:,e%lnods)                     !coordinates
     xc(:,1) = MATMUL(x(:,1:3),lc(:,1))       !lower element position
     xc(:,2) = MATMUL(x(:,4:6),lc(:,2))       !upper element position
     xc(:,3) = xc(:,2)-xc(:,1)                !distance vector between centers
     xc(:,4) = MATMUL(x(:,1:3),lc(:,3))       !proyection of node 4 on lower surface
     xc(:,5) = MATMUL(x(:,1:3),lc(:,4))       !proyection of node 5 on lower surface
     xc(:,6) = MATMUL(x(:,1:3),lc(:,5))       !proyection of node 6 on lower surface
     t(:,1) = x(:,1)-x(:,3)                   !second side
     t(:,2) = x(:,2)-x(:,3)                   !first side (-)
     CALL vecpro(t(1,1),t(1,2),t(1,3))        !normal
     CALL vecuni(3,t(1,1),long)               !direction 1
     CALL vecuni(3,t(1,3),long)               !unit normal
     CALL vecpro(t(1,3),t(1,1),t(1,2))        !direction 2
     ! compute strain measures
     str(1) = SQRT(DOT_PRODUCT(xc(:,3),xc(:,3))) -e%gausv(11) !spot elongation
     str(2) = DOT_PRODUCT(xc(:,3),t(:,1))        -e%gausv(12) !distortion dir 1
     str(3) = DOT_PRODUCT(xc(:,3),t(:,2))        -e%gausv(13) !distortion dir 2
     str(4) = DOT_PRODUCT(x(:,4)-xc(:,4),t(:,3)) -e%gausv(14) !penetration  nod 1
     str(5) = DOT_PRODUCT(x(:,5)-xc(:,5),t(:,3)) -e%gausv(15) !penetration  nod 2
     str(6) = DOT_PRODUCT(x(:,6)-xc(:,6),t(:,3)) -e%gausv(16) !penetration  nod 3
     ! forces at the spot
     str(1) = str(1)*stc/e%gausv(11)
     str(2) = str(2)*src/e%gausv(11)
     str(3) = str(3)*src/e%gausv(11)
     al = str(2) * t(:,1) + str(3)* t(:,2)  !shear force
     long = SQRT(DOT_PRODUCT(al,al))        !modulus
     ft = (al + str(1)*t(:,3))              !full force
     e%gausv(17:19) = str(1:3)
     e%gausv(19:22) = 0d0
     ! normal forces in upper nodes
     DO i=4,6
       f(:,i-3) = -ft*lc(i-3,1)  ! normal force
       f(:,i)   = ft*lc(i-3,2)  ! normal force
       IF( str(i) < 0d0 )THEN ! contact forces
         str(i) = str(i)*stcv*emass(1,e%lnods(i))
         f(:,i) = f(:,i) + str(i)*t(:,3)
         DO j=1,3
           f(:,j) = f(:,j) - str(i)*t(:,3)*lc(j,i-1)
         END DO
         e%gausv(i+16) = str(i)
       END IF
     END DO
     ! moment (forces applied on lower element)
     IF( long > 0d0 )THEN
       t(:,1) = al/long                         !shear direction
       CALL vecpro(t(1,3),t(1,1),t(1,2))        !moment direction
       dx = x(:,1)-xc(:,1)                      !first node
       b(1) = DOT_PRODUCT(dx,t(:,1))
       a(1) = DOT_PRODUCT(dx,t(:,2))
       dx = x(:,2)-xc(:,1)                      !second node
       b(2) = DOT_PRODUCT(dx,t(:,1))
       a(2) = DOT_PRODUCT(dx,t(:,2))
       dx = x(:,3)-xc(:,1)                      !second node
       b(3) = DOT_PRODUCT(dx,t(:,1))
       a(3) = DOT_PRODUCT(dx,t(:,2))
       vx =  a(2)*b(3) - a(3)*b(2)              !twice the area
       vx = vx -a(1)*b(3) + a(3)*b(1)           !twice the area
       vx = vx +a(1)*b(2) - a(2)*b(1)           !twice the area
       al = t(:,3)*e%gausv(11)*long/vx           !Moment
       f(:,1) = f(:,1) + al*(a(3)-a(2))
       f(:,2) = f(:,2) + al*(a(1)-a(3))
       f(:,3) = f(:,3) + al*(a(2)-a(1))
     END IF
     DO i=1,nnode
       j = e%lnods(i)
       resid(1:ndime,j) = resid(1:ndime,j) + f(1:ndime,i) !sums on nodes
     END DO
   END IF
   e => e%next   !point to next element
 END DO
 !IF( MOD(itera,25) == 0 )WRITE(58,"(i8,12e12.4)")itera,ddd,fff  !DEBUG
 RETURN
 END SUBROUTINE resvp1
