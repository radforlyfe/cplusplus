//
//  main.cpp
//  pic10b_assignment4

#include<iostream>
#include<string>
#include<vector>
#include<fstream>

int find_next_id();
void run_events();

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class Employee{ //Abstract class (since it includes pure virtual functions)
public:
    Employee(std::string name, std::string email);
    Employee(std::ifstream& fin);
    
    //getters: need to be const ref and const???
    const std::string& get_name() const;
    const std::string& get_email() const;
    int get_id() const;
    static int get_set_next_id();                           //getter and setter of the static next_id private member
    
    virtual void write_data(std::ofstream& fout);
    void print() const;
    
    //pure virtual functions:
    virtual void print_pay() const = 0;
    virtual void save() = 0;
    
    virtual ~Employee() = default;
    Employee(Employee&&) noexcept = default;
    Employee& operator=(Employee&&) noexcept = default;
    Employee(const Employee&) = default;
    Employee& operator=(const Employee&) = default;
    
private:
    std::string name_;
    std::string email_;
    int id_;
    static int next_id;
};

int Employee::next_id(0);                                  //initialize the static private member next_id to 0

Employee::Employee(std::string name, std::string email)\
: name_(name), email_(email), id_(get_set_next_id()){}     //do we need to initialize id?

Employee::Employee(std::ifstream& fin){
    if(fin.fail()){                                        // print error message, if file failed to open
        std::cout << "failed to open file";
        return;
    }
    // read in info from the file and store it into member variables
    std::string type;
    //getline(fin, type, '\t');   ?????
    getline(fin, name_, '\t');
    getline(fin, email_, '\t');
    fin >> id_;
}

const std::string& Employee::get_name() const{
    return name_;
}
const std::string& Employee::get_email() const{
    return email_;
}
int Employee::get_id() const{
    return id_;
}
int Employee::get_set_next_id(){                         //don't need to pass parameter since we have a helper function
    next_id = find_next_id();                            //find_next_id returns int
    return next_id;
}
void Employee::write_data(std::ofstream& fout){
    fout << name_ << '\t' << email_ << '\t' << id_;
}

void Employee::print() const{
    std::cout << name_ << '\t' << id_ << '\t' << email_ << '\n';
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class HourlyWorker: public Employee{
public:
    HourlyWorker(std::string name, std::string email, double rate, int hours = 0);
    HourlyWorker(std::ifstream& fin);
    
    void set_hours();
    void print_pay() const override; // when is it const function?
    void save() override;
    
private:
    int hours_;
    double rate_;
};

HourlyWorker::HourlyWorker(std::string name, std::string email, double rate, int hours)\
: Employee(name, email), hours_(hours), rate_(rate) {}

HourlyWorker::HourlyWorker(std::ifstream& fin): Employee(fin){
    if(fin.fail()){
        std::cout << "failed to open file";
        return;
    }
    fin >> hours_ >> rate_ ;
}

//prompt user for how many hours they worked:
void HourlyWorker::set_hours(){
    std::cout << "How many hours did " << get_name() << "work?";
    std::cin >> hours_;                                               //setting hours_ using cin!
}

void HourlyWorker::print_pay() const{
    std::cout << get_name() << " receives $" << hours_ * rate_ << '\n';
}

void HourlyWorker::save(){
    std::ofstream fout("employee" + std::to_string(get_id()) + ".txt"); //creates new file named employee[ID].txt
    if(fout.fail()){
        std::cout << "failed to open file";
        return;
    }
    fout << "hourly" << '\t';                         //stores the type of employee to the file
    write_data(fout);                                 //stores Employee data - writes the name, email, id to a file
    fout << '\t' << hours_ << '\t' << rate_;          //store data specific to Hourly employee in the file
    fout.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class SalariedWorker: public Employee{
public:
    SalariedWorker(std::string name, std::string email, double salary);
    SalariedWorker(std::ifstream& fin);
    
    void print_pay() const override; // when is it const function?
    void save() override;
private:
    double salary_;
};

SalariedWorker::SalariedWorker(std::string name, std::string email, double salary)\
: Employee(name, email), salary_(salary){}

SalariedWorker::SalariedWorker(std::ifstream& fin): Employee(fin){
    if(fin.fail()){
        std::cout << "failed to open file";
        return;
    }
    fin >> salary_;
}

void SalariedWorker::print_pay() const{
    std::cout << get_name() << "receives $ " << salary_ << '\n';
}

void SalariedWorker::save(){
    std::ofstream fout ("employee" + std::to_string(get_id()) + ".txt");
    if(fout.fail()){
        std::cout << "failed to open file";
        return;
    }
    fout << "salaried" << '\t';
    write_data(fout);
    fout << '\t' << salary_;
    fout.close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
class Company{
public:
    Company();
    void print_directory() const;
    void do_hours();
    void print_payroll() const;
    void create_salaried();
    void create_hourly();
    void create_employee();
    
private:
    std::vector<std::shared_ptr<Employee>> employees; //vector- each element is ptr to employee having a separate file
};

//reads through all the files, creates Employees of suitable type for each file, storing them as pointers
Company::Company(){
    int id = 0;
    std::ifstream fin(std::string("employee") + std::to_string(id) + std::string(".txt"));   //open file with this name
    while(fin.is_open()){                                          //need a loop through until we can open all files
        std::string type;
        getline(fin, type, '\t');                                  //or (fin >> type) or if(type.compare("hourly")==0)
        if(type == "hourly"){                                      //creates HW and stores pointer in employees vector
            auto ptr = std::make_shared<HourlyWorker>(fin);
            employees.push_back(ptr);
        }
        else if(type == "salaried"){                               //creates SW and stores pointer in employees vector
            auto ptr = std::make_shared<SalariedWorker>(fin);
            employees.push_back(ptr);
        }
        ++id;
        fin.close();
        fin = std::ifstream("employee" + std::to_string(id) + ".txt");
    }
}

//runs through the vector: displays how many employees and calls print() on all entries
void Company::print_directory() const{
    std::cout << "There are " << employees.size() << " employees: \n";
    for(auto i : employees){
        (*i).print();
    }
    std::cout << '\n';
}

//runs through the vector: through using dynamic_ptr_cast<HW>, calls set_hours() and save()
void Company::do_hours(){
    for(auto i : employees){
        auto h_ptr = std::dynamic_pointer_cast<HourlyWorker>(i);  //change the employee ptr to HourlyWorker pointer
        if(h_ptr){                                                //if ptr is not null, call the set_hour() and save()
            (*h_ptr).set_hours();
            (*h_ptr).save();
        }
    }
    std::cout << '\n';
}

//runs through the vector: calls the print_pay() on all the elements
void Company::print_payroll() const{
    for(auto i : employees){
        auto h_ptr = std::dynamic_pointer_cast<HourlyWorker>(i);
        auto s_ptr = std::dynamic_pointer_cast<SalariedWorker>(i);
        if(h_ptr){                                               //if ptr is not null, and HW call print_pay()
            (*h_ptr).print_pay();
        }
        else if(s_ptr){                                         //if ptr is not null, and SW call print_pay()
            (*s_ptr).print_pay();
        }
    }
    std::cout << '\n';
}

//prompts user for name, email, salary for SW; instantiates that class; saves it and adds it to employees
//note: due to polymorphism a derived class can be stored into a base class pointer!
void Company::create_salaried(){
    std::string name, email;
    double salary = 0;
    std::cout << "Enter name: ";
    std::cin.ignore();             //???
    std::getline(std::cin, name);
    std::cout << "Enter email: ";
    std::getline(std::cin, email);
    std::cout << "Enter salary: $";
    std::cin >> salary;
    std::cout << '\n';
    auto ptr = std::make_shared<SalariedWorker>(name, email, salary);   //creates a shared pointer of SW
    ptr->save();
    employees.push_back(ptr);                                           //saves into employees vector
}

//prompts user for name, email, rate for HW; instantiates HW class; saves it and adds it to employees
void Company::create_hourly(){
    std::string name, email;
    double rate = 0;
    std::cout << "Enter name: ";
    std::cin.ignore();              //???
    std::getline(std::cin, name);
    std::cout << "Enter email: ";
    std::getline(std::cin, email);
    std::cout << "Enter hourly pay rate: $";
    std::cin >> rate;
    std::cout << '\n';
    auto ptr = std::make_shared<HourlyWorker>(name, email, rate);    //creates a shared pointer of HW
    ptr->save();
    employees.push_back(ptr);                                        //saves into employees vector
}

//asks user what type of employee they want to create and creates it!
void Company::create_employee(){
    std::cout << "What type of employee \n";
    std::cout << "S - Salaried \n";
    std::cout << "H - Hourly \n";
    std::cout << "Abort (all about inputs)?";
    char input;
    std::cin >> input;
    if (input == 'H'){                             //if input is 'H' creates a HourlyWorker
        create_hourly();
    }
    else if (input == 'S'){                             //if input is 'S' creates a SalariedWorker
        create_salaried();
    }
    else{                                          //otherwise abort
        std::cout << "creation aborted" << '\n';
        return;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//helper function for setting the static member Employee::next_id
//start with id=0; loop through until you can open the file; return the id when you cannot open file anymore
int find_next_id(){
    int id = 0;
    std::ifstream fin(std::string("employee") + std::to_string(id) + std::string(".txt")); //std::string("employee")
    while(fin.is_open()){
        ++id;
        fin = std::ifstream("employee" + std::to_string(id) + ".txt");
    }
    return id;
}

//creates a company object and repeately prompts a user to create/display/set/print until it terminates
void run_events(){
     char input;                                          //have to initialize input outside the do loop!
    do{
        std::cout << "What would you like to do?\n";
        std::cout << "C - Create Employee\n";
        std::cout << "D - Display Current Directory\n";
        std::cout << "H - Set Hours\n";
        std::cout << "P - Print Payroll\n";
        std::cout << "Quit (all other inputs)? ";
        Company c;                                        //creates a company object
        std::cin >> input;
        if(input == 'C'){
            c.create_employee();
        }
        else if(input == 'D'){
            c.print_directory();
        }
        else if(input == 'P'){
            c.print_payroll();
        }
        else if(input == 'H'){
            c.do_hours();
        }
    } while(input == 'C' || input == 'D' || input == 'P' || input == 'H');
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    run_events();
    return 0;
}
