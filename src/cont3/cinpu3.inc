 SUBROUTINE cinpu3(maxve,iwrit,npoin,coord,top,bottom)

!.... contact input routine (NEW problem)

 IMPLICIT NONE
!     arguments
 LOGICAL, INTENT(OUT) :: bottom,top
 INTEGER (kind=4),INTENT (IN) :: iwrit,npoin,maxve
 REAL (kind=8), POINTER :: coord(:,:)

!     local variables
 INTEGER (kind=4) j,naddp,ipair,isurf,surdi,oldsr,oldpr,tsurf

 LOGICAL :: found,mods
 INTEGER (kind=4), ALLOCATABLE :: codes(:,:)
 CHARACTER(len=mnam),ALLOCATABLE:: surname(:)
 CHARACTER(len=mnam):: name
 TYPE (pair3_db), POINTER :: pair,ppair
 TYPE (surf3_db), POINTER :: surf,psurf



 mods = .FALSE.  !No modifications of previous database
 IF( npair == 0 ) CALL ini_cont3(headp,tailp)   !initializes pair list
 IF( nsurf == 0 ) CALL ini_srf3 (shead,stail)   !initializes surface list
 IF( nsurf == 0 .OR. npair == 0 )oldis = 0d0    !latest maximum displacement increment


 CALL listen('CINPU3')  !Read first line
 IF( exists('CONTRO')) THEN  !.... Title print and first line

   IF(iwrit /= 0)WRITE(lures, &
     "( //10x,'*** D A T A   F O R   C O N T A C T ***',//, &
         & 10x,'*** A L G O R I T H M   3  ***',//)",ERR=9999)


   ctime = 0d0
   IF(exists('DTIME '))THEN
     ctime = getrea('DTIME ',0d0,' Dtime to compute penalty param. ..')
     IF( ctime == 0d0) ctime = -1d0
   END IF
   wear  = exists('WEARIN')
   IF( wear ) WRITE(lures,"(15x,'Work due to Friction will be computed')",ERR=9999)
   IF( ASSOCIATED (wwear)) DEALLOCATE( wwear )   !check and release
   ALLOCATE( wwear(npoin) )    !reserve space
   wwear = 0d0                 !initialize
   print_data = exists('IWRIC',posit=j)
   IF( print_data) print_data = param(j) == 1d0

 ELSE
   backs = .TRUE.
 END IF

 !.... Modify Contact parameters
 CALL listen('CINPU3')     !read first line to find TASK
 IF (exists('MODIFY')) THEN
   CALL inpco3             !modifies pair parameters
 ELSE
   backs = .TRUE.
 END IF

 ! delete surfaces

 surdi = nsurf         !keep number of original surfaces

 CALL listen('CINPU3')   !read next line to find TASK
 IF (exists('DELSUR')) THEN
   WRITE(lures,"(' Deleted surfaces ',/)",ERR=9999)
   DO
     CALL listen('CINPU3')
     IF (exists('ENDDEL') ) EXIT
     name = get_name(posin=1,texts='! Surface to delete ',stype='SURF')  !name of surface to delete
     ! search surface in data base
     CALL srch3_srf (shead, psurf, surf , name, found)
     IF (.NOT.found) THEN
        WRITE(lures,*,ERR=9999)"CINPU4:Specified surface doesn't exist :", TRIM(name)
       !CALL runend ('NINPU3: Specified surface missing ')
     ELSE
       ! delete surface from data base
       CALL del3_srf (shead, stail, psurf, surf)
       nsurf = nsurf-1    !decrement number of existing surface
       CALL delete_name(name,5)
       mods = .TRUE.
     END IF
   END DO
 ELSE
   backs = .TRUE.
 END IF

 ! delete pairs

 CALL listen('CINPU3')
 IF (exists('DELPAI')) THEN
   WRITE(lures,"(' Deleted pairs ',/)",ERR=9999)
   DO
     CALL listen('CINPU3')
     IF (exists('ENDDEL') ) EXIT
     name = get_name(posin=1,texts='! Pair to delete ',stype='PAIR')  !name of pair to delete
     ! search for pair in data base
     CALL srch_pair3 (headp, ppair, pair, name, found)
     IF (.NOT.found) THEN
       WRITE(lures,*,ERR=9999) "CINPU3:Specified pair doesn't exist: ", TRIM(name)
       !CALL runend ("NINPU3:Specified pair doesn't exist")
     ELSE
       !delete pair from data base
       CALL del_pair3 (headp, tailp, ppair , pair)
       npair = npair - 1   !decrement number of existing pairs
       CALL delete_name(name,4)
       mods = .TRUE.
     END IF
   END DO
 ELSE
   backs = .TRUE.
 END IF

 oldpr = npair   !previous existing pairs
 oldsr = nsurf   !previous existing surfaces
 IF( mods )THEN

   ! Updates internal numbers of surfaces in pair database

   ALLOCATE ( codes(2,surdi), surname(surdi) ) !allocate auxiliar arrays
   CALL chksu3(surdi,codes,surname,tsurf)      !compute auxiliar arrays
   DO j=1,tsurf                     !for each remaining surface
     name = surname(j)              !surface name
     surf => shead                  !point to first
     isurf = 1                      !initializes position
     DO
       IF(TRIM(name) == TRIM(surf%sname))EXIT   !surface found, EXIT loop
       isurf = isurf+1              !increase counter
       IF(isurf > nsurf)CALL runend('NINPU3: surface in use deleted     ')
       surf => surf%next            !point to next surface
     END DO

     !Check if the surface will be used as SLAVE for some pairs

     pair => headp                  !point to first pair
     DO ipair=1,codes(2,j)          !times surface is used as SLAVE
       DO
         IF( TRIM(pair%slave) == TRIM(name) )EXIT  !If found EXIT loop
         pair => pair%next             !point to next pair
       END DO
       pair%islav = isurf              !assign position
       pair => pair%next               !next pair
     END DO

     !Check if the surface will be used as MASTER for some pairs

     pair => headp                 !point to first pair
     DO ipair=1,codes(1,j)         !times surface is used as MASTER
       DO
         IF( TRIM(pair%master) == TRIM(name) )EXIT !If found EXIT loop
         pair => pair%next             !point to next pair
       END DO
       pair%imast = isurf              !assign position
       pair => pair%next               !next pair
     END DO

   END DO
   DEALLOCATE ( codes, surname )  !release auxiliar arrays

 END IF

!.... input contact surfaces pairs DATA

 CALL listen('CINPU3')  !read next line to find TASK
 IF( exists('ADDCON') )CALL listen('CINPU3')  !read a second line
 IF (exists('PAIRIN') )THEN    ! pair information expected

   WRITE(lures, &
     "(/,'  C O N T A C T   S U R F A C E S   P A I R S   D A T A '/)",ERR=9999)

   DO
     CALL listen ('CINPU3')        !read a line
     IF (exists('ENDPAI')) EXIT    !end of pair data detected, EXIT
     CALL new_pair3 (pair)         !Initializes new pair
     CALL cspin3(pair)             !Read pair data
     npair = npair + 1             !increase pair counter
     CALL add_pair3 (pair, headp, tailp) !add to end of the list
   END DO
                            !set maximum number of surfaces
   !surname = surface names
   !codes = (1)times as master (2) times as slave
   naddp = npair - oldpr       !number of added pairs
   surdi = nsurf+2*naddp       !dimension for auxiliar arrays
   ALLOCATE ( codes(2,surdi), surname(surdi) )  !allocate auxiliar arrays
   CALL chksu3(surdi,codes,surname,tsurf)       !generate auxiliar arrays
   !tsurf = number of expected surfaces
   ! Read new surfaces data
   CALL csinp3(maxve,iwrit,npoin,coord,oldsr,oldpr, &
               codes,surname,tsurf,surdi)
   DEALLOCATE( codes , surname )  !release auxiliar arrays
 ELSE
   backs = .TRUE.
 END IF

 IF( ALLOCATED(surtf) )DEALLOCATE(surtf)
 IF (npair == 0) THEN    ! pair information expected
   WRITE(lures,"('No pair defined: PAIR_INFO CARD EXPECTED     ')")
 ELSE
   ALLOCATE (surtf(3,npair) )     !reserve space for total contact forces
   surtf = 0d0                    !initializes
   !.... update flags BOTTOM and TOP
   pair => headp                  !point to first pair
   DO ipair=1,npair      !Loop over each pair
     IF( pair%mtsur == -2 .OR. pair%slsur == -2 )bottom = .TRUE.
     IF( pair%mtsur ==  2 .OR. pair%slsur ==  2 )top    = .TRUE.
     pair => pair%next               !next pair
   END DO
 END IF

!      WRITE(*,"('+ CONTAC: End of initial data        ')",ERR=9999)

 nconp (3) = npair ! put number of contact pairs of cont. type 3

 RETURN
 9999 CALL runen2('')
 END SUBROUTINE cinpu3
