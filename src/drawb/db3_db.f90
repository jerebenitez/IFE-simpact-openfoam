MODULE db3_db
  USE param_db,ONLY: mnam
  IMPLICIT NONE
  SAVE

  INTEGER (kind=4) :: ndbea=0   ! number of drawbead lines
  INTEGER (kind=4) :: numtdf    ! number of drawved forces
  REAL    (kind=8) :: puncht    ! punch travel, used to define
                                ! a bounding box around the drawbead

  ! Derived type for drawbead 3 database

  TYPE db3pair_db
    CHARACTER (len=mnam) :: pname ! pair name
    CHARACTER (len=mnam) :: sname ! surface name
    INTEGER (kind=4), DIMENSION (8) :: iparm    !integer variables
      !       iparm   - parameters for drawbead-sheet pairs
      !iparm (1) = ndbpoin  number of points in the line
      !iparm (2) = nrtm     number of elements to be checked
      !iparm (3) = nmn
      !iparm (4) = mst
      !iparm (5) = nnode    number of nodes in the sheet discretization
      !iparm (6) = idbfout  code for total force output
      !iparm (7) = ncrosi
         !  - number of sheet elements intersected with a drawbead
         !    line at the initial configuration (when drawbeads are
         !    introduced)
      !iparm (8) = 1 if an element set is associated to surface
    REAL    (kind=8), DIMENSION ( 2) :: rparm    !real variables
      !rparm (1) = TMAX  Maximum drawbead force
      !rparm (2) = ELMOD Elastic modulus of the drawbd
    REAL    (kind=8), DIMENSION ( 4) :: tdbf     !drawbead force (output only)
    INTEGER (kind=4), POINTER   :: irect(:,:) ,  & ! (4,nrtm)
                                   ldbs(:,:)  ,  & ! (2,nrtm)
                                   nstini(:)  ,  & ! (MAX(1,ncrosi))
                                   nstnew(:)  ,  & ! (nrtm)
                                   nstold(:)  ,  & ! (nrtm)
                                   msr(:)     ,  & ! (nmn)
                                   nseg(:)    ,  & ! (nmn+1)
                                   lmsr(:)    ,  & ! (mst)
                                   lnd(:,:)        ! (2,ndpoin-1) DB line connectivities
  !       irect   - connectivities of sheet elements
  !       ldbs    - drawbead line segments intersecting sheet element sides
  !       nstini  - codes of the state of the sheet elements with reference
  !                 to the drawbead line when they are introduced
  !       nstnew  - codes of the state of the sheet elements with reference
  !                 to the drawbead line at the present step
  !       nstold  - codes of the state of the sheet elements with reference
  !                 to the drawbead line at the previous step
  !       msr     - sheet node numbers
  !       nseg    - pointers to sheet nodes data in lmsr array
  !       lmsr    - sheet segment (element) numbers surrounding each node
  !       lnd     -  ?????
    REAL (kind=8), POINTER     ::  fdat(:,:)  ,  & ! (3,nrtm)
                                   fdaini(:,:),  & ! (2,MAX(1,ncrosi)))
                                   xl(:,:)         ! (2,ndbpoin)
  !       fdat    - real parameters defining the state of the sheet elements
  !                 at the previous step
  !       fdaini  - local natural coordinates (ss,tt) of the midpoint
  !                 of a drawbead segment intersecting a shell element
  !                 at the initial configuration
  !       xl      - x and y coordinates of the drawbead line points
    LOGICAL,POINTER                  :: daz(:)    !Drawbead affected elements
    TYPE (db3pair_db), POINTER       :: next
  END TYPE db3pair_db
  TYPE (db3pair_db), POINTER :: headp, tailp !head and tail pairs

CONTAINS

  SUBROUTINE ini_db3 (head, tail)
    !initialize the drawbead 3 database

    !Dummy arguments
    TYPE (db3pair_db), POINTER :: head, tail

    NULLIFY (head, tail)
  END SUBROUTINE ini_db3

  SUBROUTINE new_db3(pair)
  !create a new element for the drawbead 3 database
    !Dummy arguments
    TYPE(db3pair_db),POINTER:: pair

    ALLOCATE(pair)
    pair%pname = ''
    pair%sname = ''
    pair%iparm = 0
    pair%rparm = 0d0
    NULLIFY(pair%irect, pair%ldbs, pair%nstini, pair%nstnew, pair%nstold,    &
            pair%msr, pair%nseg, pair%lmsr, pair%lnd, pair%fdat,             &
            pair%fdaini, pair%xl, pair%daz)
    NULLIFY(pair%next)

  RETURN
  END SUBROUTINE new_db3

  SUBROUTINE add_db3pair (new, head, tail)
    ! adds a pair dbase to the end of the list
    ! Dummy arguments
    TYPE (db3pair_db), POINTER :: new, head, tail

    ! Check if a list is empty
    IF (.NOT. ASSOCIATED (head)) THEN
      !list is empty, start it
      head => new
      tail => new
      NULLIFY (tail%next)

    ELSE
      ! add a pair to the list
      tail%next => new
      NULLIFY (new%next)
      tail => new

    ENDIF

  RETURN
  END SUBROUTINE add_db3pair

  SUBROUTINE srch_db3pair (head, anter, posic, name, found)
    !  searches for a pair named "name"
    !  Dummy arguments
    LOGICAL :: found
    CHARACTER (len=*) :: name ! set name
    TYPE (db3pair_db), POINTER :: head, anter, posic

    found = .FALSE.
    NULLIFY (posic,anter)
    !Check if a list is empty
    IF (ASSOCIATED (head)) THEN
      posic => head
      DO
        IF(TRIM(posic%pname) == TRIM(name)) THEN
          found = .TRUE.
          EXIT
        END IF
        IF (ASSOCIATED(posic%next) ) THEN
          anter => posic
          posic => posic%next
        ELSE
          EXIT
        END IF
      END DO
    ENDIF
    IF (.NOT.found) NULLIFY (posic,anter)

  RETURN
  END SUBROUTINE srch_db3pair

  SUBROUTINE del_db3pair (head, tail, anter, posic)
    !deletes a pair pointed with posic
    !Dummy variables
    TYPE (db3pair_db), POINTER :: head, tail, anter, posic

    IF (.NOT.ASSOCIATED (anter)) THEN
      head => posic%next
    ELSE
      anter%next => posic%next
    ENDIF
    ! if posic == tail
    IF (.NOT.ASSOCIATED (posic%next) ) tail => anter
    CALL dalloc_db3pair (posic)
    NULLIFY (anter)
  RETURN
  END SUBROUTINE del_db3pair

  SUBROUTINE dalloc_db3pair (pair)
    ! deallocates a db3pair
    !Dummy variables
    TYPE (db3pair_db), POINTER :: pair
    DEALLOCATE( pair%irect, pair%ldbs, pair%nstini, pair%nstnew,          &
                pair%nstold, pair%msr, pair%nseg, pair%lmsr, pair%fdat,   &
                pair%fdaini, pair%xl,  pair%daz)
    DEALLOCATE (pair)
  END SUBROUTINE dalloc_db3pair

   include "alloc_db3.inc"
   include "chnums.inc"
   include "chqua0.inc"
   include "chquad.inc"
   include "compar.inc"
   include "countn.inc"
   include "counts.inc"
   include "db3con.inc"
   include "db3dmp.inc"
   include "db3for.inc"
   include "db3ini.inc"
   include "db3inp.inc"
   include "db3lin.inc"
   include "db3res.inc"
   include "db3sc0.inc"
   include "db3udl.inc"
   include "dbsol3.inc"
   include "inidb0.inc"
   include "inidb0a.inc"
   include "inidb1.inc"
   include "inidb2.inc"
   include "inidb3.inc"
   include "inidb4.inc"
   include "linksd.inc"
   include "prdbln.inc"
   include "proje3.inc"
   include "projec.inc"
   include "qshfun.inc"
   include "quadin.inc"
   include "rsdbe3.inc"
   include "updnd3.inc"

END MODULE db3_db
