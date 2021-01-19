#GOS

- Для запуска вам потребуется Boost.  `sudo apt-get install libboost-all-dev`
- Используйте gcc 9.3.0 и cmake 3.16.3

Запустить make.sh из <path_to_folder_with_repo>/GOS

В server/build и client/build появятся исполняемые файлы

При запуске сервера надо передать ему порт, слово для игры и кол-ов попыток для одного клиента.
Можно подключить сколько угодно клиентов, чтобы они все играли на одном слове.
Если кол-во попыток заканчивается, то клиент завершает работу.

Клиенту при запуске пердается хост и порт для сервера


#Все тестировалось на Ubuntu 20.04 LTS
#Важно: русский язык для слов не поддерживается.