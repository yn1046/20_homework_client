## Информация о проекте

Данный проект разрабатывался с использованием CMake под WSL2 (Ubuntu). Он использует пакетный
менеджер *<span style="color:#03dbfc">conan</span>*.

Поэтому для установки пакетов следует выполнить готовый скрипт `install_pkg.sh`:

```shell
$ ./install_pkg.sh
```

##### Список участников команды

Vasiliy Nesterovich

##### Имя тимлида (по желанию)

Vasiliy Nesterovich

##### Описание выбранной идеи решения

- Вся логика работы сокетов инкапсулирована в класс `ConnectionService`. Это увеличивает гибкость и переносимость.
- Клиент разделён на два потока: принимающий и отправляющий, что позволяет независимо слать и получать сообщения.

##### Описание пользовательских типов и функций в проекте

**Enum-ы:** _ActionTypes_, _CommandTypes_. Описывают действия при входе и команды чата соответственно.

**Сервисы:** _ConnectionService_. Отвечает за сетевую работу чата.

`Методы ChatService`

```c++
// Подключиться к серверу (адрес и порт определены в препроцессоре)
void connect();

// Отправить серверу сообщение любого типа.
template<typename T>
void send_message(T value);

// Отправить серверу строку.
void send_message_string(const string &str);

// Получить сообщение от сервера.
template<typename T>
T receive_message();

// Получить строку от сервера.
string receive_message_string();

// Отключиться от сервера.
void disconnect();
```

**Контроллеры:** весь функционал данного чата управляется _ChatController_.

`Методы ChatController`

```c++
// Выбор начального действия: вход, регистрация, выход.
void initialize();

// Выполнить регистрацию.
void do_signup();

// Выполнить вход.
void do_login();

// Отключиться и завершить работу.
void do_quit();

// Открыть чат (после успешного входа/регистрации).
void enter_chat(const User &user);

// Обработчик отправления сообщений.
void handle_send();

// Обработчик приёма сообщений.
void handle_receive();

// Считать ввод.
string get_input();

// Определить команду чата.
COMMAND_TYPES parse_command(const string &command);

// Выполнить определённую команду чата.
void do_command(COMMAND_TYPES command);

// Отобразить подсказки.
static void show_help();

// Определить начальное действие.
static ACTION_TYPES get_action();
```

Также в коде присутствует хелпер _strutil_ для обработки строк.

`Функции strutil`

```c++
// Обрезать все пробелы слева.
std::string ltrim(const std::string &s)

// Обрезать все пробелы справа.
std::string rtrim(const std::string &s)

// Обрезать все пробелы и слева, и справа.
std::string trim(const std::string &s)
```

##### Пояснение, как были распределены задачи в команде (кто какую часть проекта реализовывал)

Всё сделано в одиночку