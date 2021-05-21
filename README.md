# IFE-simpact-openfoam

## Instrucciones de compilación
- [WIP] Todavía no funciona del todo 
```
git clone https://github.com/jerebenitez/IFE-simpact-openfoam
cd IFE-simpact-openfoam
mkdir -p build
cd build
cmake ..
make
```

## Avances a futuro propuestos
Agrego unas cuantas mejoras que creo que sería bueno meterle al projecto. 

- Documentación para usuarios (i.e. qué es, cómo se usa, etc)
- Documentación para desarrolladores
- Escribir tests unitarios y de integración para cada librería
- Portear código a último estándar de Fortran

Las dos primeras me parecen las más importantes, la 2da y la 3ra se pueden implementar en paralelo. 

Para la documentación del código para desarrolladores se puede usar Doxygen (u otra herramienta que las genere automáticamente), y la propuesta se extiende también a generar convenciones de desarrollo para homogeneizar el proyecto. 

La 4ta no es estrictamente necesaria aplicarla, pero si se van a seguir agregando features estaría bueno que se haga para aprovechar las cosas nuevas que se le vayan agregando al lenguaje.
