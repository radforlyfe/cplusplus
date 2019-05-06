//
//  main.cpp
//  cs32_homework3

#include <iostream>
#include <string>
using namespace std;

enum CallType {
    VOICE, TEXT
};

//////////////////////////////////////////////////////////////////////////////////////////////
class Medium{   // Base class
public:
    Medium(std::string str);
    virtual ~Medium();
    virtual std::string connect() const = 0;   // pure virtual - not allowed to create object Medium
    std::string id() const;                    // accessor of private member id
    virtual std::string transmit(std::string msg) const; // why not 0? not list here and list in TwitterAccount and inherit from there?
    
private:
    std::string id_;
};

///
Medium::Medium(std::string str): id_(str){}

Medium::~Medium(){}

std::string Medium::id() const{
    return id_;
}

std::string Medium::transmit(std::string msg) const{
    return ("text: " + msg);
}

//////////////////////////////////////////////////////////////////////////////////////////////
class TwitterAccount : public Medium{
public:
    TwitterAccount(std::string);
    virtual ~TwitterAccount();
    virtual std::string connect() const;
};

///
TwitterAccount::TwitterAccount(std::string str): Medium(str){}

TwitterAccount::~TwitterAccount(){
    cout << "Destroying the Twitter Account " << id() << "." << std::endl;
}

std::string TwitterAccount::connect() const{
    return "Tweet";
}

//////////////////////////////////////////////////////////////////////////////////////////////
class Phone: public Medium{
public:
    Phone(std::string str, CallType type);
    virtual ~Phone();
    virtual std::string connect() const;
    virtual std::string transmit(std::string msg) const;

private:
    std::string msg_;
};

///
Phone::Phone(std::string str, CallType type): Medium(str){
    switch(type){
        case VOICE:{
            msg_ = "voice:";
            break;
        }
        case TEXT:{
            msg_ = "text:";
            break;
        }
    }
}

Phone::~Phone(){
    cout << "Destroying the phone " << id() << "." << std::endl;
}

std::string Phone::connect() const{
    return "Call";
}

std::string Phone::transmit(std::string msg) const{
    return (msg_ + " " + msg);
}

//////////////////////////////////////////////////////////////////////////////////////////////
class EmailAccount: public Medium{
public:
    EmailAccount(std::string str);
    virtual ~EmailAccount();
    virtual std::string connect() const;
};

///
EmailAccount::EmailAccount(std::string str): Medium(str){}

EmailAccount::~EmailAccount(){
    cout << "Destroying the email account " << id() << "." << std::endl;
}

std::string EmailAccount::connect() const{
    return "Email";
}

//////////////////////////////////////////////////////////////////////////////////////////////
void send(const Medium* m, string msg)
{
    cout << m->connect() << " using id " << m->id()
    << ", sending " << m->transmit(msg) << endl;
}

int main()
{
    Medium* media[4];
    media[0] = new TwitterAccount("UCLABruinAlert");
    // Phone users may prefer messages to be left as voice or text.
    media[1] = new Phone("(310) 825 3894", VOICE);
    media[2] = new Phone("(213) 389 9060", TEXT);
    media[3] = new EmailAccount("jbroon@ucla.edu");
    
    cout << "Send the message." << endl;
    for (int k = 0; k < 4; k++)
        send(media[k], "Major power outage in West L.A.");
    
    // Clean up the media before exiting
    cout << "Cleaning up." << endl;
    for (int k = 0; k < 4; k++)
        delete media[k];
}
