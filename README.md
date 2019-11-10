[![Build Status](https://travis-ci.com/Toliak/lab0311.svg?branch=master)](https://travis-ci.com/Toliak/lab0311)
[![coverage](https://gitlab.toliak.ru/bmstu-cpp-3-sem/lab0311/badges/master/pipeline.svg)](https://gitlab.toliak.ru/bmstu-cpp-3-sem/lab0311/pipelines)
![Code size](https://img.shields.io/github/languages/code-size/Toliak/lab0311.svg)
![GitHub Repo size](https://img.shields.io/github/repo-size/Toliak/lab0311.svg)

# Лабораторная работа 11

> [Процесс](https://ru.wikipedia.org/wiki/Процесс_(информатика)) — программа, которая выполняется в текущий момент. Стандарт ISO 9000:2000 определяет процесс как совокупность взаимосвязанных и взаимодействующих действий, преобразующих входящие данные в исходящие.

## Задание

Написать программу на **C++** для упрощения процесса сборки, установки и упаковки проектов основанных на конфигурационных файлах **CMakeLists.txt**.

Исполняемый файл программы должен иметь название **builder** и поддерживать следующие опции запуска:

```Shell
$ ./builder --help
Usage: builder [options]
Allowed options:
  --help                    : выводим вспомогательное сообщение
  --config <Release|Debug>  : указываем конфигурацию сборки (по умолчанию Debug)
  --install                 : добавляем этап установки (в директорию _install)
  --pack                    : добавляем этап упаковки (в архив формата tar.gz)
  --timeout <count>         : указываем время ожидания (в секундах)
```

Примеры запуска программы с описанием эквивалентных запусков процессов программы **CMake**.

```Shell
$ ./builder
<=>
$ cmake -H. -B_builds -DCMAKE_INSTALL_PREFIX=_install -DCMAKE_BUILD_TYPE=Debug
$ cmake --build _builds
```

```Shell
$ ./builder --config Release
<=>
$ cmake -H. -B_builds -DCMAKE_INSTALL_PREFIX=_install -DCMAKE_BUILD_TYPE=Release
$ cmake --build _builds
```


```Shell
$ ./builder --install
<=>
$ cmake -H. -B_builds -DCMAKE_INSTALL_PREFIX=_install -DCMAKE_BUILD_TYPE=Debug
$ cmake --build _builds
$ cmake --build _builds --target install
```

```Shell
$ ./builder --pack
<=>
$ cmake -H. -B_builds -DCMAKE_INSTALL_PREFIX=_install -DCMAKE_BUILD_TYPE=Debug
$ cmake --build _builds
$ cmake --build _builds --target package
```

```Shell
$ ./builder --install --pack
<=>
$ cmake -H. -B_builds -DCMAKE_INSTALL_PREFIX=_install -DCMAKE_BUILD_TYPE=Debug
$ cmake --build _builds
$ cmake --build _builds --target install
$ cmake --build _builds --target package
```

```Shell
$ ./builder --timeout 500
<=>
$ cmake -H. -B_builds -DCMAKE_INSTALL_PREFIX=_install -DCMAKE_BUILD_TYPE=Debug
$ cmake --build _builds
```

## Требования

1. Для работы с процессами необходимо использовать библиотеку **Boost.Process** ([см. документацию](http://www.highscore.de/boost/process0.5/)).

2. Для реализации цепочки событий необходимо использовать библиотеку **Async++** ([см. документацию](https://github.com/Amanieu/asyncplusplus)).

3. В случае если время ожидания истекает, то программа завершает **все** дочерние запущенные процессы.

4. Этап установки запускается, только в случае успешного завершения процесса сборки.

5. Этап упаковки запускается, только в случаях успешного завершения процесса сборки и 
успешного завершения процесса установки.

6. Стандартные потоки вывода дочерних процессов необходимо перенаправить в стандартный поток 
вывода родительского процесса исполняемого файла **builder**.

7. Подключение библиотек [**Boost.Process**](https://docs.hunter.sh/en/latest/packages/pkg/BoostProcess.html) и [**Async++**](https://docs.hunter.sh/en/latest/packages/pkg/Async++.html) осуществить с использованием пакетного менеджера **Hunter**.

## Рекомендации

1. Для обработки параметров командной строки использовать компонент `boost::program_options`.