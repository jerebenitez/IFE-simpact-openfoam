# del 2019/09/05 al 2019/09/12
## Jere:
* compilar la versión que tenga de Simpact en Linux
    * usar el compilador de fortran (si es que consigue bajar una versión gratuita)
    * hacerlo con un *buen* makefile
    * donde *buen* significa
        * que acepte argumentos
        * que con los argumentos compile distintas *configuraciones*
        * que guarde los archivos compilados de esas *configuraciones* en una estructura de directorios adecuada
        * que use la menor cantidad de opciones de compilación posible
        * que esté bien comentado (en inglés, si es posible)
* probar la versión serial compilada
* ver qué herramienta usar para hacer debugging
## Mauro:
* pasar en limpio actividades **done**
* incorporar al Luis en el repositorio
* hacer lista deseable de configuraciones
    * incluir las opciones de compilación usadas para esas configuraciones en VisualStudio para tener de guía inicial
* pedir fuentes actualizadas a Chinesse
* buscar info sobre TecIO
### va
* las configuraciones deberían ser (las opciones de compilación son las que usa VisualStudio, no necesariamente las que queremos)
    * serial 64 debug  
        /nologo /debug:full /Od /I".\sources\inclu" /DGMNME=1 /Dacad=0 /assume:nocc_omp /warn:unused /real_size:64 /align:dcommons /align:sequence /iface:cvf /module:"Debug\\" /object:"Debug\\" /traceback /check:bounds /libs:static /threads /dbglibs /c  
        /OUT:"c:/uti/v720bd.exe" /INCREMENTAL:NO /NOLOGO /LIBPATH:"..\sources\library" /MANIFEST /MANIFESTFILE:"c:/uti/v720bd.exe.intermediate.manifest" /DEBUG /PDB:"Debug/v720b.pdb" /SUBSYSTEM:CONSOLE /IMPLIB:"c:/uti/v720bd.lib"  
        /d "_DEBUG" /l 0x0409 /fo "Debug/v720b.res"  
        /nologo /char signed /env win32 /h "v720b_h.h" /tlb "Debug/v720b.tlb"  
        /nologo /outputresource:"c:/uti/v720bd.exe;#1"  
    * serial 64 release  
        /nologo /O3 /I".\sources\inclu\\" /DGMNME=1 /Dacad=0 /assume:nocc_omp /free /warn:unused /real_size:64 /align:dcommons /align:sequence /iface:cvf /module:"Release\\" /object:"Release\\" /libs:static /threads /c  
        /OUT:"c:/uti/v720bHFdNEW.exe" /INCREMENTAL:NO /NOLOGO /LIBPATH:"../sources/library" /MANIFEST /MANIFESTFILE:"c:/uti/v720bHFdNEW.exe.intermediate.manifest" /SUBSYSTEM:CONSOLE /IMPLIB:"c:/uti/v720bHFdNEW.lib"  
        /d "NDEBUG" /l 0x0409 /fo "Release/v720b.res"  
        /nologo /char signed /env win32 /h "v720b_h.h" /tlb "Release/v720b.tlb"  
        /nologo /outputresource:"c:/uti/v720bHFdNEW.exe;#1"
    * parall 64 debug  
        /nologo /debug:full /Od /Qparallel /I".\sources\inclu" /DGMNME=1 /Dacad=0 /assume:nocc_omp /warn:unused /real_size:64 /align:dcommons /align:sequence /iface:cvf /module:"Debug Parallel\\" /object:"Debug Parallel\\" /traceback /check:bounds /libs:static /threads /dbglibs /c  
        /OUT:"c:/uti/v720bdp.exe" /INCREMENTAL:NO /NOLOGO /LIBPATH:"..\sources\library" /MANIFEST /MANIFESTFILE:"c:/uti/v720bdp.exe.intermediate.manifest" /DEBUG /PDB:"Debug Parallel/v720b.pdb" /SUBSYSTEM:CONSOLE /IMPLIB:"c:/uti/v720bdp.lib"  
        /d "_DEBUG" /l 0x0409 /fo "Debug Parallel/v720b.res"  
        /nologo /char signed /env win32 /h "v720b_h.h" /tlb "Debug Parallel/v720b.tlb"  
        /nologo /outputresource:"c:/uti/v720bdp.exe;#1"  
    * parall 64 release  
        /nologo /O3 /Qparallel /I".\sources\inclu\\" /DGMNME=1 /Dacad=0 /free /warn:unused /real_size:64 /align:dcommons /align:sequence /iface:cvf /module:"Release Parallel OMP MKL\\" /object:"Release Parallel OMP MKL\\" /libs:static /threads /c  
        /OUT:"c:/uti/v720bHFdNEWpOMPmkl.exe" /INCREMENTAL:NO /NOLOGO /LIBPATH:"../sources/library" /MANIFEST /MANIFESTFILE:"c:/uti/v720bHFdNEWpOMPmkl.exe.intermediate.manifest" /SUBSYSTEM:CONSOLE /IMPLIB:"c:/uti/v720bHFdNEWpOMPmkl.lib"  
        /d "NDEBUG" /l 0x0409 /fo "Release Parallel OMP MKL/v720b.res"  
        /nologo /char signed /env win32 /h "v720b_h.h" /tlb "Release Parallel OMP MKL/v720b.tlb"  
        /nologo /outputresource:"c:/uti/v720bHFdNEWpOMPmkl.exe;#1"  
        este es de la versión con *paralelización*, *OpenMP* y la vesión paralela de MKL
   * estas serían las que necesitamos, al menos para la **versión de Fernando de Simpact**  
   * en el caso de la versión paralela, como en general hay que probar cosas para mejorar rendimiento, pero al final uno siempre se queda con una opción, pondremos en una misma configuración los diferentes conjuntos de opciones e iremos comentando y descomentanto o usando un sistema de *if* en el que la bandera sea parte del código y no un argumento de entrada - esa es la opción para que Jere no trabaje tanto; si se vuelve imperativo, haremos algo más elaborado
