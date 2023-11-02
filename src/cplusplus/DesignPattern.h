#ifndef DESIGN_PATTERN_H
#define DESIGN_PATTERN_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>

namespace DP { // 设计模式

namespace SimpleFactory { // 简单工厂模式

class Product {
public:
  Product() = default;
  virtual ~Product() = default;
  virtual void use() = 0;
};

class ProductA : public Product {
public:
  ProductA() : name{"A"} {}
  ~ProductA() override = default;
  void use() override { std::cout << "This is a A" << std::endl; }

private:
  std::string name;
};

class ProductB : public Product {
public:
  ProductB() : name{"B"} {}
  ~ProductB() override = default;
  void use() override { std::cout << "This is a B" << std::endl; }

private:
  std::string name;
};

class Factory {
public:
  Factory() = default;
  ~Factory() = default;
  static Product *createProduct(std::string name) {
    if (name == "A") {
      return new ProductA();
    } else if (name == "B") {
      return new ProductB();
    }
    return nullptr;
  }
};

} // namespace SimpleFactory

namespace FactoryMethod { // 工厂方法模式

class Product {
public:
  Product() = default;
  virtual ~Product() = default;
  virtual void use() = 0;
};

class ProductA : public Product {
public:
  ProductA() : name{"A"} {}
  ~ProductA() override = default;
  void use() override { std::cout << "This is a A" << std::endl; }

private:
  std::string name;
};

class ProductB : public Product {
public:
  ProductB() : name{"B"} {}
  ~ProductB() override = default;
  void use() override { std::cout << "This is a B" << std::endl; }

private:
  std::string name;
};

class Factory {
public:
  Factory() = default;
  virtual ~Factory() = default;
  virtual Product *create() = 0;
};

class FactoryA : public Factory {
public:
  FactoryA() = default;
  ~FactoryA() override = default;
  Product *create() override { return new ProductA(); }
};

class FactoryB : public Factory {
public:
  FactoryB() = default;
  ~FactoryB() override = default;
  Product *create() override { return new ProductB(); }
};

} // namespace FactoryMethod

namespace AbstractFactory { // 抽象工厂模式

class Shoe {
public:
  Shoe() = default;
  virtual ~Shoe() = default;
  virtual void walk() = 0;
};

class Clothe {
public:
  Clothe() = default;
  virtual ~Clothe() = default;
  virtual void wear() = 0;
};

class NikeShoe : public Shoe {
public:
  NikeShoe() = default;
  ~NikeShoe() override = default;
  void walk() override { std::cout << "This is a Nike Shoe" << std::endl; };
};

class NikeClothe : public Clothe {
public:
  NikeClothe() = default;
  ~NikeClothe() override = default;
  void wear() override { std::cout << "This is a Nike Clothe" << std::endl; };
};

class LiNingShoe : public Shoe {
public:
  LiNingShoe() = default;
  ~LiNingShoe() override = default;
  void walk() override { std::cout << "This is a LiNing Shoe" << std::endl; };
};

class LiNingClothe : public Clothe {
public:
  LiNingClothe() = default;
  ~LiNingClothe() override = default;
  void wear() override { std::cout << "This is a LiNing Clothe" << std::endl; };
};

class Factory {
public:
  Factory() = default;
  virtual ~Factory() = default;
  virtual Shoe *createShoe() = 0;
  virtual Clothe *createClothe() = 0;
};

class NikeFactory : public Factory {
public:
  NikeFactory() = default;
  ~NikeFactory() override = default;
  Shoe *createShoe() override { return new NikeShoe(); }
  Clothe *createClothe() override { return new NikeClothe(); }
};

class LiNingFactory : public Factory {
public:
  LiNingFactory() = default;
  ~LiNingFactory() override = default;
  Shoe *createShoe() override { return new LiNingShoe(); }
  Clothe *createClothe() override { return new LiNingClothe(); }
};

} // namespace AbstractFactory

namespace Builder { // 建造者模式

class Meal {
public:
  Meal() = default;
  ~Meal() = default;
  std::string getFood() const { return food; }
  std::string getDrink() const { return drink; }
  void setFood(std::string food_) { food = food_; }
  void setDrink(std::string drink_) { drink = drink_; }

private:
  std::string food;
  std::string drink;
};

class MealBuilder {
public:
  MealBuilder() = default;
  ~MealBuilder() {
    if (meal != nullptr) {
      delete meal;
      meal = nullptr;
    }
  };
  // Step1
  void CreateMeal() {
    if (meal == nullptr) {
      meal = new Meal();
    }
  }
  // Step2
  virtual void buildFood() = 0;
  // Step3
  virtual void buildDrink() = 0;
  Meal *getMeal() {
    std::cout << "Here is a meal with " << meal->getFood() << " and "
              << meal->getDrink() << std::endl;
    return meal;
  }

protected:
  Meal *meal;
};

class MealBuilderA : public MealBuilder {
public:
  MealBuilderA() = default;
  ~MealBuilderA() = default;
  // Step2
  void buildFood() override {
    if (meal != nullptr) {
      meal->setFood("Hamburger");
    } else {
      std::cout << "No Meal" << std::endl;
    }
  }
  // Step3
  void buildDrink() override {
    if (meal != nullptr) {
      meal->setDrink("Cola");
    } else {
      std::cout << "No Meal" << std::endl;
    }
  }
};

class MealBuilderB : public MealBuilder {
public:
  MealBuilderB() = default;
  ~MealBuilderB() = default;
  // Step2
  void buildFood() override {
    if (meal != nullptr) {
      meal->setFood("Fries");
    } else {
      std::cout << "No Meal" << std::endl;
    }
  }
  // Step3
  void buildDrink() override {
    if (meal != nullptr) {
      meal->setDrink("Juice");
    } else {
      std::cout << "No Meal" << std::endl;
    }
  }
};

class KFC {
public:
  KFC() = default;
  ~KFC() = default;
  Meal *Cook() {
    builder->CreateMeal();
    builder->buildFood();
    builder->buildDrink();
    return builder->getMeal();
  }
  void setBuilder(MealBuilder *builder_) { builder = builder_; }

private:
  MealBuilder *builder;
};

} // namespace Builder

namespace Prototype { // 原型模式

struct School {
  std::string name;
};

class Student {
public:
  Student(const std::string &name_, const int &age_, School *school_)
      : name{name_}, age{age_}, school{school_} {};
  virtual ~Student() = default;
  virtual Student *clone() = 0;
  virtual void setName(const std::string &) = 0;
  virtual void setAge(const int &) = 0;
  virtual void setSchool(School *) = 0;
  virtual void introduce() = 0;

protected:
  std::string name;
  int age;
  School *school;
};

class PrimaryStudent : public Student {
public:
  PrimaryStudent(const std::string &name_, const int &age_, School *school_)
      : Student{name_, age_, school_} {};
  ~PrimaryStudent() override = default;
  PrimaryStudent(const PrimaryStudent &) = default;
  Student *clone() override { return new PrimaryStudent(*this); }
  void setName(const std::string &name_) override { name = name_; }
  void setAge(const int &age_) override { age = age_; }
  void setSchool(School *school_) override { school = school_; }
  void introduce() override {
    std::cout << "My name is " << name << ", I am " << age << " years old, "
              << "I am in " << school->name << std::endl;
  }
};

} // namespace Prototype

namespace Singleton { //单例模式

class LazySingletonwithGC {
public:
  ~LazySingletonwithGC() {
    std::cout << "Destory LazySingletonwithGC" << std::endl;
  };
  static LazySingletonwithGC *getInstance() {
    if (instance == nullptr) {
      instance = new LazySingletonwithGC();
    }
    return instance;
  }
  void use() { std::cout << "This is a LazySingletonwithGC" << std::endl; }
  class GC { // 避免手动delete getinstance()，否则不会自动调用析构函数
  public:
    ~GC() {
      printf("GC destruction\n");
      if (instance != nullptr) {
        delete instance;
        instance = nullptr;
      }
    }
  };
  static GC gc_singleton;

private:
  LazySingletonwithGC() = default;
  static LazySingletonwithGC *instance; // nullptr in .cpp
};

class HungrySingletonwithGC {
public:
  ~HungrySingletonwithGC() {
    std::cout << "Destory HungrySingletonwithGC" << std::endl;
  };
  static HungrySingletonwithGC *getInstance() { return instance; }
  void use() { std::cout << "This is a HungrySingletonwithGC" << std::endl; }
  class GC { // 避免手动delete getinstance()，否则不会自动调用析构函数
  public:
    ~GC() {
      printf("GC destruction\n");
      if (instance != nullptr) {
        delete instance;
        instance = nullptr;
      }
    }
  };
  static GC gc_singleton;

private:
  HungrySingletonwithGC() = default;
  static HungrySingletonwithGC *instance; // new HungrySingleton() in .cpp
};

class SingletonwithoutGC {
public:
  ~SingletonwithoutGC() {
    std::cout << "Destory SingletonwithoutGC" << std::endl;
  };
  static SingletonwithoutGC &getInstance() {
    static SingletonwithoutGC instance;
    return instance;
  }
  void use() { std::cout << "This is a SingletonwithoutGC" << std::endl; }

private:
  SingletonwithoutGC() = default;
};

} // namespace Singleton

namespace Adaptor { // 适配器模式

class Target {
public:
  Target() = default;
  virtual ~Target() = default;
  virtual void use() = 0;
};

class Adaptee {
public:
  Adaptee() = default;
  virtual ~Adaptee() = default;
  virtual void func(int value) {
    std::cout << "Adaptee: value = " << value << std::endl;
  }
};

// 类适配器
class ClassAdapter : public Target, public Adaptee {
public:
  ClassAdapter() = default;
  ~ClassAdapter() override = default;
  void use() override { func(3); }
  // 此处可以覆写功能函数，更具灵活性
  void func(int value) override {
    std::cout << "Adaptor: value = " << value << std::endl;
  }
};

// 对象适配器
class ObjectAdapter : public Target {
public:
  explicit ObjectAdapter(Adaptee *adaptee_) : adaptee{adaptee_} {}
  ~ObjectAdapter() = default;
  void use() override { adaptee->func(3); }

private:
  Adaptee *adaptee;
};

} // namespace Adaptor

namespace Bridge { // 桥接模式

class Color {
public:
  Color() = default;
  virtual ~Color() = default;
  virtual std::string getColor() = 0;
};

class Shape {
public:
  explicit Shape(Color *color_) : color{color_} {}
  virtual ~Shape() = default;
  virtual void show() {
    std::cout << "This is a " << getColor() << " default shape" << std::endl;
  }
  std::string getColor() { return color->getColor(); }

protected:
  Color *color;
};

class Red : public Color {
public:
  Red() : name{"Red"} {}
  ~Red() override = default;
  std::string getColor() override { return name; }

private:
  std::string name;
};

class Blue : public Color {
public:
  Blue() : name{"Blue"} {};
  ~Blue() override = default;
  std::string getColor() override { return name; }

private:
  std::string name;
};

class Circle : public Shape {
public:
  explicit Circle(Color *color_) : Shape(color_) {}
  ~Circle() override = default;
  void show() override {
    std::cout << "This is a " << getColor() << " Circle" << std::endl;
  }
};

class Square : public Shape {
public:
  explicit Square(Color *color_) : Shape(color_) {}
  ~Square() override = default;
  void show() override {
    std::cout << "This is a " << getColor() << " Square" << std::endl;
  }
};

} // namespace Bridge

namespace Decorator { // 装饰器模式

class Transformer {
public:
  Transformer() = default;
  virtual ~Transformer() = default;
  virtual void move() { std::cout << "Move!" << std::endl; }
};

class Car : public Transformer {
public:
  Car() = default;
  ~Car() override = default;
  void move() override { std::cout << "Car move" << std::endl; }
};

class Changer : public Transformer {
public:
  explicit Changer(Transformer *tf) : transformer(tf) {}
  ~Changer() override = default;
  void move() override {
    transformer->move();
    std::cout << "Change!" << std::endl;
  }

private:
  Transformer *transformer;
};

class Robot : public Changer {
public:
  Robot(Transformer *tf) : Changer(tf) {}
  ~Robot() override = default;
  void move() override {
    Changer::move();
    std::cout << "Change to a Robot" << std::endl;
    say();
  }
  void say() { std::cout << "Hey, man" << std::endl; }
};

class Plane : public Changer {
public:
  Plane(Transformer *tf) : Changer(tf) {}
  ~Plane() override = default;
  void move() override {
    Changer::move();
    std::cout << "Change to a Plane" << std::endl;
    fly();
  }
  void fly() { std::cout << "Fly to the sky" << std::endl; }
};

} // namespace Decorator

namespace Facade { // 外观模式

class SystemA {
public:
  SystemA() = default;
  ~SystemA() = default;
  void use() { std::cout << "This is SystemA" << std::endl; }
};

class SystemB {
public:
  SystemB() = default;
  ~SystemB() = default;
  void use() { std::cout << "This is SystemB" << std::endl; }
};

class SystemC {
public:
  SystemC() = default;
  ~SystemC() = default;
  void use() { std::cout << "This is SystemC" << std::endl; }
};

class Facade {
public:
  Facade() : sysA{new SystemA()}, sysB{new SystemB()}, sysC{new SystemC()} {}
  ~Facade() {
    if (sysA != nullptr) {
      delete sysA;
      sysA = nullptr;
    }
    if (sysB != nullptr) {
      delete sysB;
      sysB = nullptr;
    }
    if (sysC != nullptr) {
      delete sysC;
      sysC = nullptr;
    }
  };
  void operation() {
    sysA->use();
    sysB->use();
    sysC->use();
  }

private:
  SystemA *sysA;
  SystemB *sysB;
  SystemC *sysC;
};

} // namespace Facade

namespace Flyweight { // 享元模式

class IFlyweight {
public:
  IFlyweight() = default;
  virtual ~IFlyweight() = default;
  virtual void use() = 0;
};

class SharedFlyweight : public IFlyweight {
public:
  explicit SharedFlyweight(std::string str_) : IFlyweight{}, str{str_} {}
  ~SharedFlyweight() override = default;
  void use() override {
    std::cout << "It is [" << str << "] working now" << std::endl;
  }

private:
  std::string str;
};

class FlyweightFactory {
public:
  FlyweightFactory() = default;
  ~FlyweightFactory() = default;
  IFlyweight *getSharedFlyweight(std::string str) {
    if (fwmap.find(str) != fwmap.end()) {
      std::cout << str << " already exists" << std::endl;
      return fwmap[str];
    } else {
      std::cout << "Create " << str << std::endl;
      IFlyweight *fw = new SharedFlyweight(str);
      fwmap[str] = fw;
      return fw;
    }
  }

private:
  std::unordered_map<std::string, IFlyweight *> fwmap;
};

} // namespace Flyweight

namespace Proxy { // 代理模式

class Subject {
public:
  Subject() = default;
  virtual ~Subject() = default;
  virtual void Request() = 0;
};

class RealSubject : public Subject {
public:
  RealSubject() = default;
  ~RealSubject() override = default;
  void Request() override {
    std::cout << "This is RealSubject to handle the request" << std::endl;
  }
};

class Proxy : public Subject {
public:
  explicit Proxy(Subject *sub_) : sub{sub_} {}
  ~Proxy() override = default;
  void preRequest() { std::cout << "Before Request" << std::endl; }
  void afterRequest() { std::cout << "After Request" << std::endl; }
  void Request() {
    preRequest();
    sub->Request();
    afterRequest();
  }

private:
  Subject *sub;
};

} // namespace Proxy

namespace Responsibility { // 职责链模式

class Handler {
public:
  Handler() = default;
  virtual ~Handler() = default;
  virtual void setNext(Handler *h) { next = h; }
  virtual void request(int) = 0;

protected:
  Handler *next;
};

class HandlerA : public Handler {
public:
  explicit HandlerA(std::string name_) : Handler{}, name{name_} {};
  ~HandlerA() override = default;
  void request(int index) override {
    if (index < 10) {
      std::cout << name << " can handle this request." << std::endl;
    } else {
      std::cout << name << " can't handle this request." << std::endl;
      if (next == nullptr) {
        std::cout << "Nobody can handle this request." << std::endl;
        return;
      }
      next->request(index);
    }
  }

private:
  std::string name;
};

class HandlerB : public Handler {
public:
  explicit HandlerB(std::string name_) : Handler{}, name{name_} {};
  ~HandlerB() override = default;
  void request(int index) override {
    if (index >= 10 && index < 100) {
      std::cout << name << " can handle this request." << std::endl;
    } else {
      std::cout << name << " can't handle this request." << std::endl;
      if (next == nullptr) {
        std::cout << "Nobody can handle this request." << std::endl;
        return;
      }
      next->request(index);
    }
  }

private:
  std::string name;
};

class HandlerC : public Handler {
public:
  explicit HandlerC(std::string name_) : Handler{}, name{name_} {};
  ~HandlerC() override = default;
  void request(int index) override {
    if (index >= 100) {
      std::cout << name << " can handle this request." << std::endl;
    }
  }

private:
  std::string name;
};

} // namespace Responsibility

namespace Command { // 命令模式

class Command {
public:
  Command() = default;
  virtual ~Command() = default;
  virtual void execute() = 0;
};

class Controller {
public:
  Controller() = default;
  ~Controller() = default;
  void setCommand(std::shared_ptr<Command> command_) { command = command_; }
  void use() { command->execute(); }

private:
  std::shared_ptr<Command> command;
};

class Television {
public:
  Television() = default;
  ~Television() = default;
  void open() { std::cout << "Open the television" << std::endl; }
  void change() { std::cout << "Change the channel" << std::endl; }
  void off() { std::cout << "Close the television" << std::endl; }
};

class OpenCommand : public Command {
public:
  explicit OpenCommand(std::shared_ptr<Television> tv_) : Command{}, tv{tv_} {}
  ~OpenCommand() override = default;
  void execute() override { tv->open(); }

private:
  std::shared_ptr<Television> tv;
};

class ChangeCommand : public Command {
public:
  explicit ChangeCommand(std::shared_ptr<Television> tv_)
      : Command{}, tv{tv_} {}
  ~ChangeCommand() override = default;
  void execute() override { tv->change(); }

private:
  std::shared_ptr<Television> tv;
};

class OffCommand : public Command {
public:
  explicit OffCommand(std::shared_ptr<Television> tv_) : Command{}, tv{tv_} {}
  ~OffCommand() override = default;
  void execute() override { tv->off(); }

private:
  std::shared_ptr<Television> tv;
};

} // namespace Command

namespace Interpreter { // 解释器模式

class Variable;

class Context {
public:
  Context() = default;
  ~Context() = default;
  void add(Variable *v, int value) { maps[v] = value; }
  int get(Variable *v) { return maps[v]; }

private:
  std::unordered_map<Variable *, int> maps;
};

class Expression {
public:
  Expression() = default;
  virtual ~Expression() = default;
  virtual int interpret(Context *c) = 0;
};

class Add : public Expression {
public:
  Add(Expression *l, Expression *r) : Expression{}, left{l}, right{r} {}
  ~Add() override = default;
  int interpret(Context *c) override {
    return left->interpret(c) + right->interpret(c);
  }

private:
  Expression *left;
  Expression *right;
};

class Minus : public Expression {
public:
  Minus(Expression *l, Expression *r) : Expression{}, left{l}, right{r} {}
  ~Minus() override = default;
  int interpret(Context *c) override {
    return left->interpret(c) - right->interpret(c);
  }

private:
  Expression *left;
  Expression *right;
};

class Variable : public Expression {
public:
  Variable() = default;
  ~Variable() override = default;
  int interpret(Context *c) override { return c->get(this); }
};

} // namespace Interpreter

namespace Iterator { // 迭代器模式

class Iterator {
public:
  Iterator() = default;
  virtual ~Iterator() = default;
  virtual std::string first() = 0;
  virtual std::string next() = 0;
  virtual std::string current() = 0;
  virtual bool end() = 0;
};

class Object {
public:
  Object() = default;
  virtual ~Object() = default;
  virtual Iterator *CreateIterator() = 0;
  virtual int count() = 0;
  virtual void push(std::string) = 0;
  virtual std::string get(int) = 0;
};

class ListIterator : public Iterator {
public:
  explicit ListIterator(Object *obj_) : obj{obj_}, index{0} {}
  ~ListIterator() override = default;
  std::string first() override { return obj->get(0); }
  std::string next() override {
    if (index < obj->count()) {
      return obj->get(index++);
    } else {
      std::cout << "No element exists" << std::endl;
      return "";
    }
  }
  std::string current() override {
    if (index < obj->count()) {
      return obj->get(index);
    } else {
      std::cout << "No element exists" << std::endl;
      return "";
    }
  }
  bool end() override { return index >= obj->count(); }

private:
  Object *obj;
  int index;
};

class List : public Object {
public:
  List() = default;
  ~List() override {
    if (it != nullptr) {
      delete it;
      it = nullptr;
    }
  }
  Iterator *CreateIterator() override {
    if (it == nullptr) {
      it = new ListIterator(this);
    }
    return it;
  }
  int count() override { return vec.size(); }
  void push(std::string str) override { vec.push_back(std::move(str)); }
  std::string get(int index) {
    std::string str{""};
    if (index >= 0 && index < vec.size()) {
      str = vec[index];
    }
    return str;
  }

private:
  Iterator *it;
  std::vector<std::string> vec;
};

} // namespace Iterator

namespace Mediator { // 中介者模式

class IMediator;

class Member {
public:
  Member() = default;
  virtual ~Member() = default;
  virtual void setMediator(IMediator *) = 0;
  virtual void sendMessage(int, std::string) = 0;
  virtual void receiveMessage(std::string) = 0;
};

class IMediator {
public:
  IMediator() = default;
  virtual ~IMediator() = default;
  virtual void regist(int, Member *) = 0;
  virtual void operation(int, std::string) = 0;
};

class Mediator : public IMediator {
public:
  Mediator() = default;
  ~Mediator() override = default;
  void regist(int index, Member *mb) {
    maps[index] = mb;
    maps[index]->setMediator(this);
  }
  void operation(int index, std::string str) override {
    if (maps.find(index) == maps.cend()) {
      std::cout << "No such a member named " << index << std::endl;
    } else {
      maps[index]->receiveMessage(str);
    }
  }

private:
  std::unordered_map<int, Member *> maps;
};

class MemeberA : public Member {
public:
  MemeberA() = default;
  ~MemeberA() override = default;
  void setMediator(IMediator *md) override { md_ = md; }
  void sendMessage(int index, std::string str) override {
    std::cout << "Send message from A: " << str << std::endl;
    md_->operation(index, str);
  }
  void receiveMessage(std::string str) override {
    std::cout << "Member A receive: " << str << std::endl;
  }

private:
  IMediator *md_;
};

class MemeberB : public Member {
public:
  MemeberB() = default;
  ~MemeberB() override = default;
  void setMediator(IMediator *md) override { md_ = md; }
  void sendMessage(int index, std::string str) override {
    std::cout << "Send message from B: " << str << std::endl;
    md_->operation(index, str);
  }
  void receiveMessage(std::string str) override {
    std::cout << "Member B receive: " << str << std::endl;
  }

private:
  IMediator *md_;
};

} // namespace Mediator

namespace Memento { // 备忘录模式

class Mememto {
public:
  Mememto(int att, int def, int l) : attack{att}, defense{def}, life{l} {}
  ~Mememto() = default;
  int getAttack() { return attack; }
  int getDefense() { return defense; }
  int getLife() { return life; }

private:
  int attack;
  int defense;
  int life;
};

class Player {
public:
  Player() = default;
  ~Player() = default;
  int getAttack() { return attack; }
  int getDefense() { return defense; }
  int getLife() { return life; }
  void setAttack(int att) { attack = att; }
  void setDefense(int def) { defense = def; }
  void setLife(int l) { life = l; }
  void Init() {
    std::cout << "Init State" << std::endl;
    setAttack(100);
    setDefense(100);
    setLife(100);
  }
  void Fusion() {
    std::cout << "Fusion State" << std::endl;
    setAttack(1e9);
    setDefense(1e9);
    setLife(1e9);
  }
  void Fight() {
    std::cout << "Fight with Nidhoggur" << std::endl;
    setAttack(0);
    setDefense(0);
    setLife(0);
  }
  Mememto *Save() { return new Mememto(getAttack(), getDefense(), getLife()); }
  void Load(Mememto *m) {
    if (m == nullptr) {
      std::cout << "Init State" << std::endl;
      return;
    }
    std::cout << "Load State" << std::endl;
    setAttack(m->getAttack());
    setDefense(m->getDefense());
    setLife(m->getLife());
  }
  void Display() {
    std::cout << "Attack: " << attack << std::endl;
    std::cout << "Defense: " << defense << std::endl;
    std::cout << "Life: " << life << std::endl;
  }

private:
  int attack;
  int defense;
  int life;
};

class SL {
public:
  SL() = default;
  ~SL() = default;
  Mememto *get(std::string str) {
    if (mememto.find(str) == mememto.end()) {
      std::cout << "No such a state" << std::endl;
      return nullptr;
    } else {
      return mememto[str];
    }
  }
  void set(std::string str, Mememto *m) { mememto[str] = m; }

private:
  std::unordered_map<std::string, Mememto *> mememto;
};

} // namespace Memento

namespace Observer { // 观察者模式

class Observer {
public:
  Observer() = default;
  virtual ~Observer() = default;
  virtual void update() = 0;
};

class Subject {
public:
  Subject() = default;
  virtual ~Subject() = default;
  virtual void action() = 0;
  void attach(Observer *ob) { obs.push_back(ob); }

protected:
  std::vector<Observer *> obs;
};

class Police : public Subject {
public:
  Police() = default;
  ~Police() override = default;
  void action() {
    std::cout << "Police is coming" << std::endl;
    for (auto &ob : obs) {
      ob->update();
    }
  }
};

class Thief : public Observer {
public:
  Thief() = default;
  ~Thief() override = default;
  void update() override { std::cout << "Run!" << std::endl; }
};

class Someone : public Observer {
public:
  Someone() = default;
  ~Someone() override = default;
  void update() override { std::cout << "Help me!" << std::endl; }
};

} // namespace Observer

namespace State { // 状态模式

class Machine;

class IState {
public:
  IState() = default;
  virtual ~IState() = default;
  virtual void action(Machine *machine) = 0;
  virtual std::string get() = 0;
};

class Machine {
public:
  Machine();
  ~Machine() = default;
  void action() { state->action(this); }
  void set(IState *st) { state = st; }
  void get() { std::cout << state->get() << std::endl; }

private:
  IState *state;
};

class Init : public IState {
public:
  ~Init() = default;
  static Init &getInstance() {
    static Init instance;
    return instance;
  }
  void action(Machine *machine) override;
  std::string get() { return "Init"; }

private:
  Init() = default;
};

class Work : public IState {
public:
  ~Work() = default;
  static Work &getInstance() {
    static Work instance;
    return instance;
  }
  void action(Machine *machine) override;
  std::string get() { return "Work"; }

private:
  Work() = default;
};

class Quit : public IState {
public:
  ~Quit() = default;
  static Quit &getInstance() {
    static Quit instance;
    return instance;
  }
  void action(Machine *machine) override;
  std::string get() { return "Quit"; }

private:
  Quit() = default;
};

class Terminate : public IState {
public:
  ~Terminate() = default;
  static Terminate &getInstance() {
    static Terminate instance;
    return instance;
  }
  void action(Machine *machine) override {
    std::cout << "Sorry, something wrong, break!" << std::endl;
  }
  std::string get() { return "Terminate"; }

private:
  Terminate() = default;
};

Machine::Machine() { state = &Init::getInstance(); }

void Init::action(Machine *machine) {
  std::cout << "Init..." << std::endl;
  int success = rand() % 10;
  std::cout << "Init: " << success << std::endl;
  if (success < 8) {
    std::cout << "Init succeed" << std::endl;
    machine->set(&(Work::getInstance()));
  } else {
    std::cout << "Init failed" << std::endl;
    machine->set(&(Terminate::getInstance()));
  }
}

void Work::action(Machine *machine) {
  std::cout << "Work..." << std::endl;
  int success = rand() % 10;
  std::cout << "Work: " << success << std::endl;
  if (success < 6) {
    std::cout << "Work succeed" << std::endl;
    machine->set(&(Quit::getInstance()));
  } else {
    std::cout << "Work failed" << std::endl;
    machine->set(&(Terminate::getInstance()));
  }
}

void Quit::action(Machine *machine) {
  std::cout << "Quit..." << std::endl;
  int success = rand() % 10;
  std::cout << "Quit: " << success << std::endl;
  if (success < 8) {
    std::cout << "Quit succeed" << std::endl;
  } else {
    std::cout << "Quit failed" << std::endl;
    machine->set(&(Terminate::getInstance()));
  }
}

} // namespace State

namespace Strategy { // 策略模式

class IStrategy {
public:
  IStrategy() = default;
  virtual ~IStrategy() = default;
  virtual void solve() = 0;
};

class StrategyA : public IStrategy {
public:
  StrategyA() = default;
  ~StrategyA() override = default;
  void solve() override { std::cout << "Using the strategyA" << std::endl; }
};

class StrategyB : public IStrategy {
public:
  StrategyB() = default;
  ~StrategyB() override = default;
  void solve() override { std::cout << "Using the strategyB" << std::endl; }
};

class Client {
public:
  Client() = default;
  ~Client() = default;
  void setStrategy(IStrategy *st) { strategy = st; }
  void solve() { strategy->solve(); }

private:
  IStrategy *strategy;
};

} // namespace Strategy

namespace TemplateMethod { // 模板方法模式

class Customer {
public:
  Customer() = default;
  virtual ~Customer() = default;
  virtual void add() { std::cout << "add" << std::endl; }
  virtual void calculate() = 0;
  virtual void pay() { std::cout << "pay" << std::endl; }
  void shopping() {
    add();
    calculate();
    pay();
  }
};

class Normal : public Customer {
public:
  Normal() = default;
  ~Normal() override = default;
  void calculate() override { std::cout << "100% price" << std::endl; }
};

class VIP : public Customer {
public:
  VIP() = default;
  ~VIP() override = default;
  void calculate() override { std::cout << "80% price" << std::endl; }
};

} // namespace TemplateMethod

namespace Visitor { // 访问者模式

class IVisitor;

class Card {
public:
  Card() = default;
  ~Card() = default;
  virtual void accept(IVisitor *) = 0;
};

class GCard : public Card {
public:
  GCard() = default;
  ~GCard() = default;
  void accept(IVisitor *vis);
};

class SCard : public Card {
public:
  SCard() = default;
  ~SCard() = default;
  void accept(IVisitor *vis);
};

class IVisitor {
public:
  IVisitor() = default;
  ~IVisitor() = default;
  // 被观察者种类固定
  virtual void acceptG(GCard *) = 0;
  virtual void acceptS(SCard *) = 0;
};

// 双分派，取决于本身类型，也取决于vis类型
void GCard::accept(IVisitor *vis) { vis->acceptG(this); }
void SCard::accept(IVisitor *vis) { vis->acceptS(this); }

class Lab : public IVisitor {
public:
  Lab() = default;
  ~Lab() = default;
  void acceptG(GCard *g) override {
    std::cout << "You are G-Level, can not enter the lab." << std::endl;
  }
  void acceptS(SCard *s) override {
    std::cout << "You are S-Level, welcome to the lab." << std::endl;
  }
};

class Room : public IVisitor {
public:
  Room() = default;
  ~Room() = default;
  void acceptG(GCard *g) override {
    std::cout << "You are G-Level, welcome home." << std::endl;
  }
  void acceptS(SCard *s) override {
    std::cout << "You are S-Level, welcome home." << std::endl;
  }
};

class Train : public IVisitor {
public:
  Train() = default;
  ~Train() = default;
  void acceptG(GCard *g) override {
    std::cout << "You are G-Level, wait for the train." << std::endl;
  }
  void acceptS(SCard *s) override {
    std::cout << "You are S-Level, the train is waiting for you." << std::endl;
  }
};

class School {
public:
  School() = default;
  ~School() = default;
  void push(Card *c) { vec.push_back(c); }
  void accept(IVisitor *vis) {
    for (auto &c : vec) {
      c->accept(vis);
    }
  }

private:
  std::vector<Card *> vec;
};

} // namespace Visitor

} // namespace DP

#endif
