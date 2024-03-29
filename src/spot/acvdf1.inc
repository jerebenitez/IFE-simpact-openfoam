 SUBROUTINE acvdf1(ndime,nnode,ndofn,nelem,ifpre,heade)
 !******************************************************************
 !
 !*** activates degrees of freedom
 !
 !******************************************************************
 IMPLICIT NONE
 INTEGER(kind=4),INTENT(IN) :: ndime,nnode,ndofn,nelem
 INTEGER(kind=4),INTENT(OUT) :: ifpre(:,:)
 TYPE(ele01), POINTER :: heade

 INTEGER (kind=4) ielem,j,n
 TYPE(ele01), POINTER :: e

 !*** activates degrees of freedom

 e => heade
 DO ielem=1,nelem
   DO j=1,nnode
     n=e%lnods(j)
     IF( n > 0 ) THEN
       ifpre(1:ndime,n) = 0
       IF( e%rot) ifpre(ndime+1:ndofn,n) = 0
     END IF
   END DO
   e => e%next
 END DO

 RETURN
 END SUBROUTINE acvdf1
