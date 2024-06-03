#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Car
{
public:
  string name;
  vector<Car *> subtypes;

  Car(const string &name) : name(name) {}
  virtual ~Car()
  {
    for (auto subtype : subtypes)
    {
      delete subtype;
    }
  }

  void addSubtype(Car *subtype)
  {
    subtypes.push_back(subtype);
  }

  virtual void display()
  {
    cout << name << endl;
  }

  virtual string getType() const
  {
    return "Car";
  }
};
class Passenger : public Car
{
public:
  Passenger(string name) : Car(name) {}

  string getType() const override
  {
    return "Passenger";
  }
};
class Sedan : public Passenger
{
public:
  Sedan(string name) : Passenger(name) {}

  string getType() const override
  {
    return "Sedan";
  }
};
class Coupe : public Passenger
{
public:
  Coupe(string name) : Passenger(name) {}

  string getType() const override
  {
    return "Coupe";
  }
};
class Race : public Car
{
public:
  Race(string name) : Car(name) {}

  string getType() const override
  {
    return "Race";
  }
};
class Rally : public Race
{
public:
  Rally(string name) : Race(name) {}

  string getType() const override
  {
    return "Rally";
  }
};
class Bolide : public Race
{
public:
  Bolide(string name) : Race(name) {}

  string getType() const override
  {
    return "Bolide";
  }
};
class Work : public Car
{
public:
  Work(string name) : Car(name) {}

  string getType() const override
  {
    return "Work";
  }
};
class Truck : public Work
{
public:
  Truck(string name) : Work(name) {}

  string getType() const override
  {
    return "Truck";
  }
};


Car *setupCarTree()
{
  auto root = new Car("Car");

  auto passenger = new Passenger("Passenger");
  auto race = new Race("Race");
  auto work = new Work("Work");
  root->addSubtype(passenger);
  root->addSubtype(race);
  root->addSubtype(work);

  auto sedan = new Sedan("Sedan");
  auto coupe = new Coupe("Coupe");
  passenger->addSubtype(sedan);
  passenger->addSubtype(coupe);

  auto rally = new Rally("Rally");
  auto bolide = new Bolide("Bolide");
  race->addSubtype(rally);
  race->addSubtype(bolide);

  auto truck = new Truck("Truck");
  work->addSubtype(truck);

  return root;
}
class TreeNavigator
{
  Car *current;
  Car *root;
  vector<Car *> path;

public:
  TreeNavigator(Car *root) : current(root), root(root)
  {
    path.push_back(root);
  }

  void moveUp()
  {
    if (path.size() > 1)
    {
      path.pop_back();
      current = path.back();
    }
    else
      cout << "Already at the root.\n";
  }
  void moveDown(const string &name)
  {
    if (path.size() != 3)
    {
      for (auto subtype : current->subtypes)
      {
        if (subtype->name == name)
        {
          current = subtype;
          path.push_back(current);
          return;
        }
      }
      cout << "No node with name: " << name << "\n";
    }
    else
      cout << "Already at the bottom.\n";
  }
  void createNewSubtype(const string &name)
  {
    if (path.size() == 3)
    {
      Car *newSubtype = nullptr;

      if (typeid(*current) == typeid(Sedan))
        newSubtype = new Sedan(name);
      if (typeid(*current) == typeid(Coupe))
        newSubtype = new Coupe(name);
      if (typeid(*current) == typeid(Rally))
        newSubtype = new Rally(name);
      if (typeid(*current) == typeid(Bolide))
        newSubtype = new Bolide(name);
      if (typeid(*current) == typeid(Truck))
        newSubtype = new Truck(name);

      current->addSubtype(newSubtype);
      cout << "Created new object: " << name << "\n";
    }
    else
      cout << "You can't create objects on this node!\n";
  }
  void deleteSubtype(const string &name)
  {
    if (path.size() == 3)
    {
      for (auto it = current->subtypes.begin(); it != current->subtypes.end(); ++it)
      {
        if ((*it)->name == name)
        {
          delete *it;
          current->subtypes.erase(it);
          cout << "Deleted subtype: " << name << "\n";
          return;
        }
      }
      cout << "No subtype with name: " << name << "\n";
    }
    else
      cout << "You can't delete objects on this node!\n";
  }
  void modifySubtype(const string &oldName, const string &newName)
  {
    if (path.size() == 3)
    {
      for (auto subtype : current->subtypes)
      {
        if (subtype->name == oldName)
        {
          subtype->name = newName;
          cout << "Modified object: " << oldName << " to " << newName << "\n";
          return;
        }
      }
      cout << "No object with name: " << oldName << "\n";
    }
    else
      cout << "You can't delete objects on this node!\n";
  }
  void listSubtypes()
  {
    cout << "Listing all descendants of " << current->name << ":\n";
    listSubtypesRecursive(current, 1);
  }
  void saveToFile(const string &filename)
  {
    ofstream ofs(filename);
    if (ofs)
    {
      for(auto child1 : root->subtypes) {
        for(auto child2 : child1->subtypes) {
          for(auto child3 : child2->subtypes) {
            ofs << child3->getType() << " " << child3->name << "\n";
          }
        }
      }
      cout << "Tree saved to " << filename << "\n";
    }
    else
    {
      cout << "Failed to open file: " << filename << "\n";
    }
  }
  void loadFromFile(const string &filename)
  {
    ifstream ifs(filename);
    if (ifs)
    {
      string type, name;
      while (ifs >> type >> name)
      {
        Car *newSubtype = nullptr;

        if(type == "Sedan") {
          newSubtype = new Sedan(name);
          root->subtypes[0]->subtypes[0]->addSubtype(newSubtype);
        }
        if(type == "Coupe"){
          newSubtype = new Coupe(name);
          root->subtypes[0]->subtypes[1]->addSubtype(newSubtype);
        }
        if(type == "Rally") {
          newSubtype = new Rally(name);
          root->subtypes[1]->subtypes[0]->addSubtype(newSubtype);
        }
        if(type == "Bolide") {
          newSubtype = new Bolide(name);
          root->subtypes[1]->subtypes[1]->addSubtype(newSubtype);
        }
        if(type == "Truck") {
          newSubtype = new Truck(name);
          root->subtypes[2]->subtypes[0]->addSubtype(newSubtype);
        }
      }
    }
    else
    {
      cout << "Failed to open file: " << filename << std::endl;
    }
  }
  void displayCurrent()
  {
    cout << "Current node: ";
    current->display();
    for (int i = 0; i < current->subtypes.size(); ++i)
    {
      cout << i + 1 << ". " << current->subtypes[i]->name << "\n";
    }
  }

private:
  void listSubtypesRecursive(Car *node, int level)
  {
    for (auto subtype : node->subtypes)
    {
      if (typeid(*node) == typeid(Sedan))
        cout << subtype->name << "\n";
      if (typeid(*node) == typeid(Coupe))
        cout << subtype->name << "\n";
      if (typeid(*node) == typeid(Rally))
        cout << subtype->name << "\n";
      if (typeid(*node) == typeid(Bolide))
        cout << subtype->name << "\n";
      if (typeid(*node) == typeid(Truck))
        cout << subtype->name << "\n";
      listSubtypesRecursive(subtype, level + 1);
    }
  }
};

enum CommandType
{
  MOVE,
  CREATE,
  DELETE,
  MODIFY,
  DIR,
  SHOW,
  SAVE,
  READ,
  TREE,
  HELP,
  EXIT,
  INVALID
};
struct Command
{
  CommandType type;
  string argument1, argument2;
};
Command parseCommand(const string &input)
{
  istringstream stream(input);
  string command, argument1, argument2;
  stream >> command >> argument1 >> argument2;

  // usuwanie spacji z poczatku i konca
  argument1.erase(0, argument1.find_first_not_of(" \t"));
  argument1.erase(argument1.find_last_not_of(" \t") + 1);

  if (command == "cd")
    return {MOVE, argument1, ""};
  if (command == "mo")
    return {CREATE, argument1, ""};
  if (command == "do")
    return {DELETE, argument1, ""};
  if (command == "mdo")
    return {MODIFY, argument1, argument2};
  if (command == "dir")
    return {DIR, "", ""};
  if (command == "show")
    return {SHOW, argument1, ""};
  if (command == "save")
    return {SAVE, argument1, ""};
  if (command == "read")
    return {READ, argument1, ""};
  if (command == "tree")
    return {TREE, "", ""};
  if (command == "help")
    return {HELP, "", ""};
  if (command == "exit")
    return {EXIT, "", ""};
  return {INVALID, "", ""};
}

int main()
{
  Car *root = setupCarTree();
  TreeNavigator navigator(root);

  string input;
  while (true)
  {
    cout << "> ";
    getline(cin, input);

    Command command = parseCommand(input);
    switch (command.type)
    {
    case MOVE:
      if (!command.argument1.empty())
      {
        if (command.argument1 == "..")
          navigator.moveUp();
        else
          navigator.moveDown(command.argument1);
      }
      else
        cout << "ERROR: invalid argument!\n";

      break;

    case CREATE:
      if (!command.argument1.empty())
        navigator.createNewSubtype(command.argument1);
      else
        cout << "ERROR: invalid argument!\n";
      break;

    case DELETE:
      if (!command.argument1.empty())
        navigator.deleteSubtype(command.argument1);
      else
        cout << "ERROR: invalid argument!\n";
      break;

    case MODIFY:
      if (!command.argument1.empty() && !command.argument2.empty())
        navigator.modifySubtype(command.argument1, command.argument2);
      else
        cout << "ERROR: invalid arguments!\n";
      break;

    case DIR:
      navigator.listSubtypes();
      break;

    case SHOW:
      navigator.displayCurrent();
      break;

    case SAVE:
      if (!command.argument1.empty())
        navigator.saveToFile(command.argument1);
      else
        cout << "ERROR: invalid argument!\n";
      break;

    case READ:
      if (!command.argument1.empty())
        navigator.loadFromFile(command.argument1);
      else
        cout << "ERROR: invalid argument!\n";
      break;

    case TREE:
      cout << "Car\n";
      cout << "  Passenger\n";
      cout << "    Sedan\n";
      cout << "    Coupe\n";
      cout << "  Race\n";
      cout << "    Rally\n";
      cout << "    Bolide\n";
      cout << "  Work\n";
      cout << "    Truck\n";
      break;

    case HELP:
      cout << "cd [name|..]\tMove across the class hierarchy.\n";
      cout << "mo [name]\tCreate a new object.\n";
      cout << "do [name]\tDelete an object.\n";
      cout << "mdo [name]\tModify an object.\n";
      cout << "show [name]\tShow information about object.\n";
      cout << "dir\t\tDisplay all objects inheriting from current node.\n";
      cout << "save [filename]\tSave current program state to file.\n";
      cout << "read [filename]\tRead program state from file.\n";
      cout << "tree\t\tDisplay class hierarchy.\n";
      cout << "help\t\tDisplay help.\n";
      cout << "exit\t\tExit the program\n";
      break;

    case EXIT:
      delete root;
      return 0;

    case INVALID:
      cout << "Invalid command! Type 'help' to see the list of available commands.\n";
      break;
    }
  }
}