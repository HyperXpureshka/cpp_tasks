#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// Утилита для цветного вывода
#define COLOR_RESET "\033[0m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RED "\033[31m"

void printTaskHeader(int taskNum, const string& description) {
    cout << COLOR_YELLOW << "[ ЗАДАНИЕ " << taskNum << " ]" << COLOR_RESET << endl;
    cout << description << "\n" << COLOR_GREEN << "Результат:" << COLOR_RESET << endl;
}

// Задание 1
class Shape {
public:
    virtual void translate(double x, double y) {
        if (x < -1000 || x > 1000 || y < -1000 || y > 1000) {
            throw invalid_argument("Недопустимые координаты для перемещения");
        }
    }
    virtual ~Shape() = default;
};

class Circle : public Shape {
    double radius;
public:
    Circle(double r) : radius(r) {}
    void translate(double x, double y) override {
        Shape::translate(x, y);
        cout << "Круг перемещен на (" << x << ", " << y << ")" << endl;
    }
};

class Rectangle : public Shape {
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    void translate(double x, double y) override {
        Shape::translate(x, y);
        cout << "Прямоугольник перемещен на (" << x << ", " << y << ")" << endl;
    }
};

// Задание 2
class Database {
public:
    virtual void connect(const string& connectionString) {
        if (connectionString.empty()) {
            throw runtime_error("Ошибка подключения: строка подключения пуста");
        }
    }
    virtual ~Database() = default;
};

class MySQLDatabase : public Database {
public:
    void connect(const string& connectionString) override {
        Database::connect(connectionString);
        cout << "Успешное подключение к MySQL: " << connectionString << endl;
    }
};

class SQLiteDatabase : public Database {
public:
    void connect(const string& connectionString) override {
        Database::connect(connectionString);
        cout << "Успешное подключение к SQLite: " << connectionString << endl;
    }
};

// Задание 3
class Task {
public:
    virtual void execute() {
        throw runtime_error("Попытка выполнения неинициализированной задачи");
    }
    virtual ~Task() = default;
};

class PrintTask : public Task {
    string message;
public:
    PrintTask(const string& msg) : message(msg) {}
    void execute() override {
        cout << "Печать: " << message << endl;
    }
};

class EmailTask : public Task {
    string email, subject, body;
public:
    EmailTask(const string& e, const string& s, const string& b) 
        : email(e), subject(s), body(b) {}
    void execute() override {
        cout << "Отправка email на " << email << ": " << subject << endl;
    }
};

// Задание 4
class ShapePerimeter {
public:
    virtual double getPerimeter() const {
        throw runtime_error("Некорректные параметры фигуры");
    }
    virtual ~ShapePerimeter() = default;
};

class Triangle : public ShapePerimeter {
    double a, b, c;
public:
    Triangle(double side1, double side2, double side3) : a(side1), b(side2), c(side3) {
        if (a <= 0 || b <= 0 || c <= 0 || a + b <= c || a + c <= b || b + c <= a) {
            throw invalid_argument("Некорректные стороны треугольника");
        }
    }
    double getPerimeter() const override { return a + b + c; }
};

class Square : public ShapePerimeter {
    double side;
public:
    Square(double s) : side(s) {
        if (side <= 0) throw invalid_argument("Сторона квадрата должна быть положительной");
    }
    double getPerimeter() const override { return 4 * side; }
};

// Задание 5
class WeatherService {
public:
    virtual string getForecast() const {
        throw runtime_error("Данные прогноза недоступны");
    }
    virtual ~WeatherService() = default;
};

class LocalWeatherService : public WeatherService {
public:
    string getForecast() const override {
        return "Местный прогноз: Солнечно, +25°C";
    }
};

class RemoteWeatherService : public WeatherService {
public:
    string getForecast() const override {
        return "Удаленный прогноз: Облачно, +18°C";
    }
};

// Задание 6
class Transaction {
public:
    virtual void commit() {
        throw runtime_error("Ошибка выполнения транзакции");
    }
    virtual ~Transaction() = default;
};

class BankTransaction : public Transaction {
    double amount;
public:
    BankTransaction(double amt) : amount(amt) {}
    void commit() override {
        cout << "Банковская транзакция на сумму " << amount << " выполнена" << endl;
    }
};

class CryptoTransaction : public Transaction {
    string crypto;
    double amount;
public:
    CryptoTransaction(const string& cr, double amt) : crypto(cr), amount(amt) {}
    void commit() override {
        cout << "Криптотранзакция " << crypto << " на сумму " << amount << " выполнена" << endl;
    }
};

// Задание 7
class Notification {
public:
    virtual void send(const string& recipient, const string& message) {
        throw runtime_error("Ошибка отправки уведомления");
    }
    virtual ~Notification() = default;
};

class EmailNotification : public Notification {
public:
    void send(const string& recipient, const string& message) override {
        cout << "Email отправлен на " << recipient << ": " << message << endl;
    }
};

class SMSNotification : public Notification {
public:
    void send(const string& recipient, const string& message) override {
        cout << "SMS отправлено на " << recipient << ": " << message << endl;
    }
};

// Задание 8
class ShapeBoundingBox {
public:
    virtual vector<pair<double, double>> getBoundingBox() const {
        throw runtime_error("Некорректные параметры фигуры");
    }
    virtual ~ShapeBoundingBox() = default;
};

class CircleBB : public ShapeBoundingBox {
    double x, y, radius;
public:
    CircleBB(double centerX, double centerY, double r) : x(centerX), y(centerY), radius(r) {
        if (radius <= 0) throw invalid_argument("Радиус должен быть положительным");
    }
    vector<pair<double, double>> getBoundingBox() const override {
        return {{x - radius, y - radius}, {x + radius, y + radius}};
    }
};

class Polygon : public ShapeBoundingBox {
    vector<pair<double, double>> points;
public:
    Polygon(const vector<pair<double, double>>& pts) : points(pts) {
        if (points.size() < 3) throw invalid_argument("Полигон должен иметь хотя бы 3 точки");
    }
    vector<pair<double, double>> getBoundingBox() const override {
        if (points.empty()) return {};
        double minX = points[0].first, maxX = points[0].first;
        double minY = points[0].second, maxY = points[0].second;
        for (const auto& p : points) {
            minX = min(minX, p.first);
            maxX = max(maxX, p.first);
            minY = min(minY, p.second);
            maxY = max(maxY, p.second);
        }
        return {{minX, minY}, {maxX, maxY}};
    }
};

// Задание 9
class UserProfile {
public:
    virtual void updateProfile(const string& username, const string& email) {
        if (username.empty() || email.empty()) {
            throw invalid_argument("Имя пользователя и email не могут быть пустыми");
        }
        if (email.find('@') == string::npos) {
            throw invalid_argument("Некорректный email");
        }
    }
    virtual ~UserProfile() = default;
};

class AdminProfile : public UserProfile {
public:
    void updateProfile(const string& username, const string& email) override {
        UserProfile::updateProfile(username, email);
        cout << "Профиль администратора " << username << " обновлен" << endl;
    }
};

class GuestProfile : public UserProfile {
public:
    void updateProfile(const string& username, const string& email) override {
        UserProfile::updateProfile(username, email);
        cout << "Гостевой профиль " << username << " обновлен" << endl;
    }
};

// Задание 10
class PaymentProcessor {
public:
    virtual void processPayment(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Сумма платежа должна быть положительной");
        }
    }
    virtual ~PaymentProcessor() = default;
};

class CreditCardProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) override {
        PaymentProcessor::processPayment(amount);
        cout << "Обработка кредитной карты на сумму " << amount << endl;
    }
};

class DebitCardProcessor : public PaymentProcessor {
public:
    void processPayment(double amount) override {
        PaymentProcessor::processPayment(amount);
        cout << "Обработка дебетовой карты на сумму " << amount << endl;
    }
};

// Задание 11
class ShapeReflect {
public:
    virtual void reflect(bool overX, bool overY) {
        if (!overX && !overY) {
            throw invalid_argument("Должна быть хотя бы одна ось отражения");
        }
    }
    virtual ~ShapeReflect() = default;
};

class CircleReflect : public ShapeReflect {
public:
    void reflect(bool overX, bool overY) override {
        ShapeReflect::reflect(overX, overY);
        cout << "Круг отражен по оси X: " << boolalpha << overX 
             << ", по оси Y: " << overY << endl;
    }
};

class RectangleReflect : public ShapeReflect {
public:
    void reflect(bool overX, bool overY) override {
        ShapeReflect::reflect(overX, overY);
        cout << "Прямоугольник отражен по оси X: " << boolalpha << overX 
             << ", по оси Y: " << overY << endl;
    }
};

// Задание 12
class FileReader {
public:
    virtual string read(const string& filename) {
        if (filename.empty()) {
            throw invalid_argument("Имя файла не может быть пустым");
        }
        return "";
    }
    virtual ~FileReader() = default;
};

class TextFileReader : public FileReader {
public:
    string read(const string& filename) override {
        FileReader::read(filename);
        return "Содержимое текстового файла " + filename;
    }
};

class BinaryFileReader : public FileReader {
public:
    string read(const string& filename) override {
        FileReader::read(filename);
        return "Двоичные данные из файла " + filename;
    }
};

// Задание 13
class ShapeArea {
public:
    virtual double getArea() const {
        throw runtime_error("Некорректные параметры фигуры");
    }
    virtual ~ShapeArea() = default;
};

class Ellipse : public ShapeArea {
    double a, b;
public:
    Ellipse(double major, double minor) : a(major), b(minor) {
        if (a <= 0 || b <= 0) throw invalid_argument("Оси эллипса должны быть положительными");
    }
    double getArea() const override { return 3.14159 * a * b; }
};

class SquareArea : public ShapeArea {
    double side;
public:
    SquareArea(double s) : side(s) {
        if (side <= 0) throw invalid_argument("Сторона квадрата должна быть положительной");
    }
    double getArea() const override { return side * side; }
};

// Задание 14
class EmailService {
public:
    virtual void sendEmail(const string& to, const string& subject, const string& body) {
        if (to.empty() || subject.empty()) {
            throw invalid_argument("Получатель и тема не могут быть пустыми");
        }
    }
    virtual ~EmailService() = default;
};

class SMTPService : public EmailService {
public:
    void sendEmail(const string& to, const string& subject, const string& body) override {
        EmailService::sendEmail(to, subject, body);
        cout << "Email отправлен через SMTP на " << to << ": " << subject << endl;
    }
};

class APIService : public EmailService {
public:
    void sendEmail(const string& to, const string& subject, const string& body) override {
        EmailService::sendEmail(to, subject, body);
        cout << "Email отправлен через API на " << to << ": " << subject << endl;
    }
};

// Задание 15
class Game {
    bool active = false;
public:
    virtual void endGame() {
        if (!active) {
            throw runtime_error("Нельзя завершить неактивную игру");
        }
        active = false;
    }
    virtual void startGame() { active = true; }
    virtual ~Game() = default;
};

class ChessGame : public Game {
public:
    void endGame() override {
        Game::endGame();
        cout << "Шахматная игра завершена" << endl;
    }
};

class FootballGame : public Game {
public:
    void endGame() override {
        Game::endGame();
        cout << "Футбольный матч завершен" << endl;
    }
};

// Задание 16
class ShapeVertices {
public:
    virtual vector<pair<double, double>> getVertices() const {
        throw runtime_error("Некорректные параметры фигуры");
    }
    virtual ~ShapeVertices() = default;
};

class TriangleVert : public ShapeVertices {
    vector<pair<double, double>> vertices;
public:
    TriangleVert(pair<double, double> v1, pair<double, double> v2, pair<double, double> v3) {
        vertices = {v1, v2, v3};
        // Проверка на коллинеарность точек
        double area = (v2.first - v1.first) * (v3.second - v1.second) - 
                      (v2.second - v1.second) * (v3.first - v1.first);
        if (area == 0) throw invalid_argument("Точки треугольника не должны быть коллинеарны");
    }
    vector<pair<double, double>> getVertices() const override { return vertices; }
};

class Pentagon : public ShapeVertices {
    vector<pair<double, double>> vertices;
public:
    Pentagon(const vector<pair<double, double>>& v) : vertices(v) {
        if (v.size() != 5) throw invalid_argument("Пентагон должен иметь 5 вершин");
    }
    vector<pair<double, double>> getVertices() const override { return vertices; }
};

// Задание 17
class Session {
    bool active = false;
public:
    virtual void startSession() {
        if (active) {
            throw runtime_error("Сессия уже активна");
        }
        active = true;
    }
    virtual void endSession() { active = false; }
    virtual ~Session() = default;
};

class UserSession : public Session {
public:
    void startSession() override {
        Session::startSession();
        cout << "Пользовательская сессия начата" << endl;
    }
};

class AdminSession : public Session {
public:
    void startSession() override {
        Session::startSession();
        cout << "Административная сессия начата" << endl;
    }
};

// Задание 18
class ShapeColor {
    string color;
public:
    ShapeColor(const string& c) : color(c) {
        if (c.empty()) throw invalid_argument("Цвет не может быть пустым");
    }
    virtual string getColor() const {
        if (color.empty()) throw runtime_error("Цвет не установлен");
        return color;
    }
    virtual ~ShapeColor() = default;
};

class CircleColor : public ShapeColor {
public:
    CircleColor(const string& c) : ShapeColor(c) {}
    string getColor() const override {
        return "Цвет круга: " + ShapeColor::getColor();
    }
};

class SquareColor : public ShapeColor {
public:
    SquareColor(const string& c) : ShapeColor(c) {}
    string getColor() const override {
        return "Цвет квадрата: " + ShapeColor::getColor();
    }
};

// Задание 19
class Logger {
public:
    virtual void log(const string& message) {
        if (message.empty()) {
            throw invalid_argument("Сообщение лога не может быть пустым");
        }
    }
    virtual ~Logger() = default;
};

class FileLogger : public Logger {
public:
    void log(const string& message) override {
        Logger::log(message);
        cout << "Запись в файл лога: " << message << endl;
    }
};

class ConsoleLogger : public Logger {
public:
    void log(const string& message) override {
        Logger::log(message);
        cout << "Вывод в консоль: " << message << endl;
    }
};

// Задание 20
class DataProcessor {
    public:
        virtual void processData(const string& data) {
            if (data.empty()) {
                throw invalid_argument("Данные не могут быть пустыми");
            }
        }
        virtual ~DataProcessor() = default;
    };
    
    class CSVProcessor : public DataProcessor {
    public:
        void processData(const string& data) override {
            DataProcessor::processData(data);
            cout << "Обработка CSV данных: " << data << endl;
        }
    };
    
    class JSONProcessor : public DataProcessor {
        public:
            void processData(const string& data) override {
                DataProcessor::processData(data);
                
                // Простая проверка на валидность JSON (начало и конец должны быть {})
                if (data.front() != '{' || data.back() != '}') {
                    throw invalid_argument("Некорректный формат JSON");
                }
                
                cout << "Обработка JSON данных: " << data << endl;
            }
        };
        
// Главная функция для демонстрации работы всех заданий
int main() {
    try {
        // Задание 1
        printTaskHeader(1, "Проверка перемещения фигур");
        Circle circle(5.0);
        circle.translate(10, 20);
        Rectangle rect(3.0, 4.0);
        rect.translate(-5, 30);

        // Задание 2
        printTaskHeader(2, "Проверка подключения к базам данных");
        MySQLDatabase mysql;
        mysql.connect("host=localhost;user=root;password=1234");
        SQLiteDatabase sqlite;
        sqlite.connect("file:test.db");

        // Задание 3
        printTaskHeader(3, "Проверка выполнения задач");
        PrintTask printTask("Тестовое сообщение");
        printTask.execute();
        EmailTask emailTask("test@example.com", "Привет", "Это тестовое письмо");
        emailTask.execute();

        // Задание 4
        printTaskHeader(4, "Проверка периметров фигур");
        Triangle triangle(3, 4, 5);
        cout << "Периметр треугольника: " << triangle.getPerimeter() << endl;
        Square square(5);
        cout << "Периметр квадрата: " << square.getPerimeter() << endl;

        // Задание 5
        printTaskHeader(5, "Проверка сервисов погоды");
        LocalWeatherService localWeather;
        cout << localWeather.getForecast() << endl;
        RemoteWeatherService remoteWeather;
        cout << remoteWeather.getForecast() << endl;

        // Задание 6
        printTaskHeader(6, "Проверка транзакций");
        BankTransaction bankTrans(1000.50);
        bankTrans.commit();
        CryptoTransaction cryptoTrans("BTC", 0.5);
        cryptoTrans.commit();

        // Задание 7
        printTaskHeader(7, "Проверка уведомлений");
        EmailNotification emailNotif;
        emailNotif.send("user@example.com", "Ваш заказ готов");
        SMSNotification smsNotif;
        smsNotif.send("+79123456789", "Ваш код подтверждения: 1234");

        // Задание 8
        printTaskHeader(8, "Проверка ограничивающих рамок фигур");
        CircleBB circleBB(0, 0, 10);
        auto bb = circleBB.getBoundingBox();
        cout << "Circle BB: (" << bb[0].first << "," << bb[0].second << "), (" 
             << bb[1].first << "," << bb[1].second << ")" << endl;
        Polygon polygon({{0,0}, {0,5}, {5,5}, {5,0}});
        bb = polygon.getBoundingBox();
        cout << "Polygon BB: (" << bb[0].first << "," << bb[0].second << "), (" 
             << bb[1].first << "," << bb[1].second << ")" << endl;

        // Задание 9
        printTaskHeader(9, "Проверка обновления профилей");
        AdminProfile admin;
        admin.updateProfile("admin", "admin@example.com");
        GuestProfile guest;
        guest.updateProfile("guest123", "guest@example.com");

        // Задание 10
        printTaskHeader(10, "Проверка обработки платежей");
        CreditCardProcessor creditCard;
        creditCard.processPayment(100.50);
        DebitCardProcessor debitCard;
        debitCard.processPayment(50.25);

        // Задание 11
        printTaskHeader(11, "Проверка отражения фигур");
        CircleReflect circleReflect;
        circleReflect.reflect(true, false);
        RectangleReflect rectReflect;
        rectReflect.reflect(true, true);

        // Задание 12
        printTaskHeader(12, "Проверка чтения файлов");
        TextFileReader textReader;
        cout << textReader.read("test.txt") << endl;
        BinaryFileReader binaryReader;
        cout << binaryReader.read("data.bin") << endl;

        // Задание 13
        printTaskHeader(13, "Проверка площадей фигур");
        Ellipse ellipse(5, 3);
        cout << "Площадь эллипса: " << ellipse.getArea() << endl;
        SquareArea squareArea(4);
        cout << "Площадь квадрата: " << squareArea.getArea() << endl;

        // Задание 14
        printTaskHeader(14, "Проверка отправки email");
        SMTPService smtp;
        smtp.sendEmail("recipient@example.com", "Важное письмо", "Привет...");
        APIService api;
        api.sendEmail("user@example.com", "Уведомление", "Ваш аккаунт...");

        // Задание 15
        printTaskHeader(15, "Проверка игр");
        ChessGame chess;
        chess.startGame();
        chess.endGame();
        FootballGame football;
        football.startGame();
        football.endGame();

        // Задание 16
        printTaskHeader(16, "Проверка вершин фигур");
        TriangleVert triangleVert({0,0}, {0,3}, {4,0});
        auto vertices = triangleVert.getVertices();
        cout << "Треугольник: ";
        for (const auto& v : vertices) cout << "(" << v.first << "," << v.second << ") ";
        cout << endl;
        Pentagon pentagon({{0,0}, {1,2}, {3,3}, {4,1}, {2,-1}});
        vertices = pentagon.getVertices();
        cout << "Пентагон: ";
        for (const auto& v : vertices) cout << "(" << v.first << "," << v.second << ") ";
        cout << endl;

        // Задание 17
        printTaskHeader(17, "Проверка сессий");
        UserSession userSession;
        userSession.startSession();
        userSession.endSession();
        AdminSession adminSession;
        adminSession.startSession();
        adminSession.endSession();

        // Задание 18
        printTaskHeader(18, "Проверка цветов фигур");
        CircleColor circleColor("красный");
        cout << circleColor.getColor() << endl;
        SquareColor squareColor("синий");
        cout << squareColor.getColor() << endl;

        // Задание 19
        printTaskHeader(19, "Проверка логгеров");
        FileLogger fileLogger;
        fileLogger.log("Система запущена");
        ConsoleLogger consoleLogger;
        consoleLogger.log("Ошибка: файл не найден");

        // Задание 20
        printTaskHeader(20, "Проверка обработки данных");
        CSVProcessor csvProcessor;
        csvProcessor.processData("id,name,age\n1,John,30");
        JSONProcessor jsonProcessor;
        jsonProcessor.processData("{\"name\":\"John\",\"age\":30}");

    } catch (const exception& e) {
        cout << COLOR_RED << "Ошибка: " << e.what() << COLOR_RESET << endl;
    }

    return 0;
}