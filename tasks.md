# del 2019/09/05 al 2019/09/12
## Jere:
1. compilar la versión que tenga de Simpact en Linux
    1. usar el compilador de ~~fortran~~ intel? (si es que consigue bajar una versión gratuita)
    2. hacerlo con un *buen* makefile
        1. Agregar instrucciones sobre cómo agregar archivos/librerías nuevos
    4. donde *buen* significa
        * que acepte argumentos
        * que con los argumentos compile distintas *configuraciones*
        * que guarde los archivos compilados de esas *configuraciones* en una estructura de directorios adecuada
        * que use la menor cantidad de opciones de compilación posible
        * que esté bien comentado (en inglés, si es posible)
2. probar la versión serial compilada
3. [DONE] ~~ver qué herramienta usar para hacer debugging~~

### Notas
1. 1. Al momento de investigar, la versión gratuita de ifort que se podía conseguir, era sólo si se estaba trabajando en un proyecto open source. No creo que intel vaya a cambiar eso, pero no es algo que se pueda asegurar a futuro.
    2. Se decidió usar **cmake** para generar el makefile en vez de hacerlo "a mano". Esta última opción hacía que el makefile fuese muy complicado de mantener. Queda ver cómo pasarle los parámetros necesarios (más específicamente, qué parámetros pasarle, el cómo viene dado por cmake).
2. _En proceso_
3. Para debugging se puede usar gdb directamente si se tolera debugguear en la terminal 😛

## Mauro:
* pasar en limpio actividades <- **done**
* incorporar al Luis en el repositorio <- **¿puedo hacerlo yo? lo intenté y no me salió**
* hacer lista deseable de configuraciones <- **done**
    * incluir las opciones de compilación usadas para esas configuraciones en VisualStudio para tener de guía inicial
* pedir fuentes actualizadas a Chinesse
* buscar info sobre TecIO <- **done**
* **pasar este archivo al proyecto Simpact**
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
* sobre TecIO:
   * info [acá](https://www.tecplot.com/products/tecio-library/)
   * más resumido [acá](http://download.tecplot.com/docs/TecplotTecIODatasheet.pdf)
   * un resumen
      * Dynamic libraries for TecIO are shipped with Tecplot 360. They are found in the bin folder of the Tecplot 360 installation, header (include) files are found in the include folder and example programs are found beneath the util/tecio folder. All platforms supported by Tecplot 360 are supported by the static and dynamic TecIO libraries.
      * TecIO uses a C API, so it can easily be called from C, C++, or Fortran. The tecio/examples folder contains both C++ and Fortran examples.
      * no puedo bajar las fuentes porque no tengo usuario
   * agregué una carpeta que se llama TecIO y puse los archivos que tengo
   * nunca supimos cómo hacer andar las librerias para Fortran con Fernando
