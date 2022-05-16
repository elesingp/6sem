# 6sem
HM for 6th sem

1.1
  При распараллеливании программ необходимо обращать внимание на целесообразность данного действия: если оптимизация не стоит потраченного времени, то смысла в этом нет. Например, при написании небольшого кода не имеет смысла что-либо распараллеливать, так как скорее всего это приведет к незначительным изменениям, а если задача еще и линейна (данные в структуре зависят друг от друга) - к частичной потере данных.
  Сам процесс распараллеливания зависит от архитектуры машины. 
  Также "ядра" следует нагружать равномерно, для достижения максимальной эфффективности программы.


1.2
Атомарный тип данных – это такие данные, разделение которых на составляющие приводит к потере их смысла с точки зрения решаемой задачи.
Операция называется атомарной, если на уровне процессора она выполняется за 1 действие
Переменная называется атомарной, если операции с ней являются атомарными.
Они, например, необходимы в тех случаях, когда два потока используют общую переменную и при этом один из них производит запись.
Атомарные загрузки дают гарантию на то, что при распараллеливании не произойдет разрыва данных (при пренебрежении атомарными данными происходит разрыв операций чтения и записи (torn read/write), что приводит к неопределенности - состояние гонок по данным (data race)).
