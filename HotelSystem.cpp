/*********************************************************************** Matr.-Nr: 3133115
Nachname/Surname: Jaffer
Vorname/Given name: Hayyan
Uni-Email: hayyan.jaffer@stud.uni-due.de
Studiengang/Course of studis: Bsc Computer Engineering(Software)
**********************************************************************/
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
using namespace::std;

int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

// Date
class Date {
private:
    short unsigned day;
    short unsigned month;
    short unsigned year;
    

public:
    Date(){}
    Date(short yearP, short monthP, short dayP){
        day = dayP;
        month = monthP;
        year = yearP;
    }

    short getDay() {
        return(day);
    }
    void setDay(short dayP) {
        day = dayP;
    }
    short getMonth() {
        return(month);
    }
    void setMonth(short monthP) {
        month = monthP;
    }
    short getYear() {
        return(year);
    }
    void setYear(short yearP) {
        year = yearP;
    }
    void getDate() {
        cout << year << "-" << month << "-" << day;
    }
    Date operator+(int days) {
        int days_left = day + days;
        int month_after = month;
        int year_after = year;

        while (days_left > daysInMonth[month_after - 1]) {
            days_left -= daysInMonth[month_after - 1];
            if (month_after == 12) {
                year_after += 1;
                month_after = 1;
            }
            else {
                month_after += 1;
            }
        }

        return(Date(year_after, month_after, days_left));
    }

    friend ostream& operator<<(ostream& output, Date& date) {
        return output << date.year << "-" << date.month << "-" << date.day;
    }

    friend istream& operator>>(istream& input, Date& date) {
        char delimeter = '-';
        input >> date.year >> delimeter >> date.month >> delimeter >> date.day;
        return input;
    }

};

// Enumerator
enum class Board {
    n,
    b,
    h,
    a
};

ostream& operator<<(ostream& output, const Board board) {
    switch (board) {
    case Board::n:
        output << "no_meals";
        break;

    case Board::b:
        output << "breakfast";
        break;
    case Board::h:
        output << "half board";
        break;
    case Board::a:
        output << "all inclusive";
        break;
    }
    return output;
}

istream& operator>>(istream& input, const Board board) {
    string s_board;
    cin >> s_board;

    while (s_board != "a" || s_board != "b" || s_board != "h" || s_board != "n") {
        cout << "Wrong input! Please input again: ";
        cin >> s_board;
    }
    
    Board in_board;
    if (s_board == "a") {
        in_board = Board::a;
    }
    else if (s_board == "b") {
        in_board = Board::b;
    }
    else if (s_board == "h") {
        in_board = Board::h;
    }
    else {
        in_board = Board::n;
    }

    return input >> in_board;
}

float getPrice(const Board board) {
    float price;
    switch (board) {
    case Board::n:
        price = 0;
        break;
    case Board::b:
        price = 10;
        break;
    case Board::h:
        price = 20;
        break;
    case Board::a:
        price = 50;
        break;
    }
    return price;
}

void printBoard() {
    cout << "a all inclusive (50.00 EUR/day)\nb breakfast(10.00 EUR / day)\nh half board(20.00 EUR / day)\nn no meals" << endl;
}

//Transport
class Transport {
public:
    Transport() {}

    virtual ~Transport() {
        cout << "Transport destructor called" << endl;
    }
    virtual bool includedTransfor() {
        return false;
    }
    virtual float get_price() {
        return(0);
    }
    virtual void print() {};
};

//Selftravel
class SelfTravel : public Transport {
public:
    SelfTravel() {}
    virtual ~SelfTravel() {
        cout << "SelfTravel destructor called" << endl;
    }
    virtual float get_price() {
        return(0);
    }
    virtual void print() {
        cout << "self travel" << endl;
    }
};

//PublicTransport
class PublicTransport : public Transport {
protected:
    Date departure;
    string code;
    string from;
    string to;
    float priceOneSeat;
    bool firstClass;
public:
    PublicTransport(Date departureP, string codeP, string fromP, string toP, float priceOneSeatP, bool firstClassP = false) {
        departure = departureP;
        code = codeP;
        from = fromP;
        to = toP;
        priceOneSeat = priceOneSeatP;
        firstClass = firstClassP;
    }
    virtual ~PublicTransport() {
        cout << "PublicTransport destructor called " << code << " at " << departure << " from " << " to " << to << endl;
    }
    virtual void print() {
        cout << "Date " << departure << " code " << code << " from " << from << " to " << to;
        if (firstClass) {
            cout << " (first class)" << endl;
        }
    }
};

//Flight
class Flight : public PublicTransport {
protected:
    bool transfer;
public:
    Flight(Date departureP, string codeP, string fromP, string toP, float price_one_seat, bool first_class = false, bool has_transfer = true) :PublicTransport(departureP, codeP, fromP, toP, price_one_seat, first_class) {
        transfer = has_transfer;
    }
    ~Flight() {
        cout << "Flight destructor called " << endl;
    }
    virtual bool includedTransfer() {
        return transfer;
    }
    virtual float get_price() {
        float price;
        if (firstClass) {
            price = 2 * priceOneSeat;
        }
        else {
            price = priceOneSeat;
        }
        return price;
    }
    virtual void print() {
        cout << "flight: " << departure << " " << code << " from " << from << " to " << to << " ";
        if (firstClass) {
            cout << "first class";
        }
        cout << " (" << get_price() << ".00 EUR/person) ";
        if (transfer) {
            cout << "transfer included";
        }
        cout << endl;
    }
};

//Train
class Train : public PublicTransport {
public:
    Train(Date departureP, string codeP, string fromP, string toP, float price_one_seat, bool first_class = false) :PublicTransport(departureP, codeP, fromP, toP, price_one_seat, first_class) {
    }
    ~Train() {
        cout << "Train destructor called " << endl;
    }

    virtual float get_price() {
        float price;
        if (firstClass) {
            price = 1.5 * priceOneSeat;
        }
        else {
            price = priceOneSeat;
        }
        return price;
    }
    virtual void print() {
        cout << "flight: " << departure << " " << code << " from " << from << " to " << to << " ";
        if (firstClass) {
            cout << "first class";
        }
        cout << " (" << get_price() << ".00 EUR/person) " << endl;
    }
};

//Accomodation
class Accomodation{
private:
    string location;
    int nights;
    int singles;
    int doubles;
    Date check_in_date;
    float priceNightSingle;
    float priceNightDouble;
    float priceOneDayParking;
    Board board;
    bool parking;

public:
    Accomodation(float priceNightSingleP, float priceNightDoubleP, float priceOneDayParkingP) {
        priceNightSingle = priceNightSingleP;
        priceNightDouble = priceNightDoubleP;
        priceOneDayParking = priceOneDayParkingP;
    }

    ~Accomodation() {
        //Show message
    }

    void ask_data() {
        location = in_location();
        check_in_date = in_arrival();
        nights = in_checkout();
        in_guests();
        printBoard();
        board = in_board_item();
        parking = in_parking();
        cout << "price: " << getPrice() << endl;
        cout << "\n";
    }
    string in_location() {
        cout << "location of accomodation: ";
        string in_location;
        cin >> in_location;
        return(in_location);
    }
    Date in_arrival() {
        cout << "arrival on (yyyy-mm-dd): ";
        Date arrival_date = Date(1, 1, 1);
        cin >> arrival_date;
        return(arrival_date);
    }
    int in_checkout() {
        cout << "how many nights (maximum 4 weeks): ";
        int in_nights;
        cin >> in_nights;
        while (in_nights > 28) {
            cout << "Maximum of 28 days allowed! Enter again : ";
            cin >> in_nights;
        }
        return(in_nights);
    }
    void in_guests() {
        cout << "how many single bed rooms (" << priceNightSingle << " EUR/night): ";
        int in_single_rooms;
        cin >> in_single_rooms;
        cout << "how many double bed rooms (" << priceNightDouble << " EUR/night): ";
        int in_double_rooms;
        cin >> in_double_rooms;
        singles = in_single_rooms;
        doubles = in_double_rooms;
    }
    Board in_board_item() {
        string in_user;
        cout << "your choice: ";
        Board in_board;
        cin >> in_user;
        while (true) {
            if (in_user == "a" || in_user == "b" || in_user == "h" || in_user == "n") {
                break;
            }
            cout << "Wong input! Input again: ";
            cin >> in_user;
        }
        if (in_user == "a") {
            in_board = Board::a;
        }
        else if (in_user == "b") {
            in_board = Board::b;
        }
        else if (in_user == "h") {
            in_board = Board::h;
        }
        else if (in_user == "n") {
            in_board = Board::n;
        }
        return(in_board);
    }
    bool in_parking() {
        cout << "with parking place (10.00 EUR/day; y(es) or n(o)):";
        string in_parking;
        cin >> in_parking;
        while(true){
            if (in_parking == "y" || in_parking == "n") {
                break;
            }
            cout << "Wrong input! Enter again: ";
            cin >> in_parking;
        }
        if (in_parking == "y") {
            return(true);
        }
        if (in_parking == "n") {
            return(false);
        }
    }
    string getLocation() {
        return(location);
    }
    int getSingles() {
        return(singles);
    }
    int getDoubles() {
        return(doubles);
    }
    int getPriceNightSingle() {
        return(priceNightSingle);
    }
    int getPriceNightDouble() {
        return(priceNightDouble);
    }
    int getNights() {
        return(nights);
    }
    Board getBoard() {
        return(board);
    }
    bool getParking() {
        return(parking);
    }
    Date getCheckInDate() {
        return(check_in_date);
    }
    int getPrice() {
        int single_rooms_cost = getSingles() * getPriceNightSingle();
        int double_rooms_cost = getDoubles() * getPriceNightDouble();
        Board board = getBoard();
        int board_cost = 0;
        if (board == Board::a) {
            board_cost = 50;
        }
        else if (board == Board::b) {
            board_cost = 10;
        }
        else if (board == Board::h) {
            board_cost = 20;
        }
        int parking_cost = 0;
        if (getParking()) {
            parking_cost = 10;
        }
        return(single_rooms_cost + double_rooms_cost + board_cost + parking_cost);
    }
};

//Request
class Request {
private:
    int no;
    Accomodation* accomodation;
    Request* next;
    Transport* transportOutward;
    Transport* transportReturn;

public:
    static int lastNo;
    Request(Accomodation* accomodationP, Request* nextP=nullptr, Transport* transportOutwardP=nullptr, Transport* transportReturnP=nullptr) {
        accomodation = accomodationP;
        next = nextP;
        no = lastNo;
        lastNo++;
        transportOutward = transportOutwardP;
        transportReturn = transportReturnP;
    }
    ~Request() {
        delete(accomodation);
        delete(transportOutward);
        delete(transportReturn);
        cout << "Request has been deleted." << endl;
    }
    int getNo() {
        return no;
    }
    void setNo(int noP) {
        no = noP;
    }
    Request* getNext() {
        return(next);
    }
    void setNext(Request* next_request) {
        next = next_request;
    }
    void print() {
        cout << "\n";
        cout << "***** REQUEST: " << no << " *****" << endl;
        cout << "accomodation at:    " << accomodation->getLocation() << endl;
        cout << "number of guests:   " << (accomodation->getSingles() + accomodation->getDoubles()) << endl;
        cout << "number of nights:   " << accomodation->getNights() << endl;
        Date check_in_date = accomodation->getCheckInDate();
        cout << "check in date:      " << check_in_date << endl;
        Date check_out_date = check_in_date + accomodation->getNights();
        cout << "check-out date:     " << check_out_date << endl;
        cout << "single bed room(s): " << accomodation->getSingles() << " (" << accomodation->getPriceNightSingle() << " EUR/night)" << endl;
        cout << "double bed room(s): " << accomodation->getDoubles() << " (" << accomodation->getPriceNightDouble() << " EUR/night)" << endl;
        cout << "board:              ";
        Board board = accomodation->getBoard();
        if (board == Board::a) {
            cout << "all inclusive (50.00 EUR/day)" << endl;
        }
        else if (board == Board::b) {
            cout << "breakfast (10.00 EUR/day)" << endl;
        }
        else if (board == Board::h) {
            cout << "half board (20.00 EUR/day)" << endl;
        }
        else if (board == Board::n) {
            cout << "no meals" << endl;
        }
        cout << "parking:            ";
        if (accomodation->getParking()) {
            cout << "included (10.00 EUR/day)" << endl;
        }
        else {
            cout << "no parking place booked" << endl;
        }
        cout << "outward journey:    ";
        transportOutward->print();
        cout << "journey back:       ";
        transportReturn->print();
        cout << "price total: " << getPrice() << ".00 EUR" << endl;
        cout << "\n";
    }

    float getPrice() {
        float accomodation_cost = accomodation->getPrice();
        float travel_cost;
        float from_cost = transportOutward->get_price() * (accomodation->getSingles() + accomodation->getDoubles());
        float to_cost = transportReturn->get_price() * (accomodation->getSingles() + accomodation->getDoubles());
        travel_cost = from_cost + to_cost;
        return(accomodation_cost + travel_cost);
    }
};

//CallCenter
class CallCenter {
private: 
    Request* requests;

public:
    CallCenter() {
        requests = nullptr;
    }

    void append(Request* request) {
        Request* newRequest = request;
        if (requests == nullptr) {
            requests = newRequest;
            return;
        }
        Request* temp = requests;
        while (temp->getNext() != nullptr) {

            temp = temp->getNext();
        }
        temp->setNext(newRequest);

        return;
    }

    void cancel(Request* request_cancel) {
        if (requests != nullptr) {
            if (requests == request_cancel) {
                requests = requests->getNext();
            }
            else {
                Request* current_request = requests;

                while (current_request->getNext() != nullptr) {
                    if (current_request->getNext() == request_cancel) {
                        current_request->setNext(current_request->getNext()->getNext());
                        break;
                    }
                    current_request = current_request->getNext();
                }
            }
        }
    }
    void print_all() {
        Request* current_request = requests;
        while (current_request != nullptr) {
            current_request->print();
            current_request = current_request->getNext();
        }
    }
    Request* getRequest(int request_no) {
        Request* current_request = requests;
        while (requests != nullptr) {
            if (current_request->getNo() == request_no) {
                return(current_request);
            }
            else {
                current_request = current_request->getNext();
            }
        }
        return NULL;
    }
};

Transport* inputTransport(Date departure) {
    cout << "0 self travel\n1 by flight\n2 by train" << endl;
    string user_input;
    cin >> user_input;
    while (true) {
        if (user_input == "0" || user_input == "1" || user_input == "2") {
            break;
        }
        else {
            cout << "Wrong input! Input again: ";
            cin >> user_input;
        }
    }
    if (user_input == "0") {
        return(new SelfTravel());
    }
    else if (user_input == "1") {
        cout << "code of flight: ";
        string flight_code;
        cin >> flight_code;

        cout << "airport of departure: ";
        string airport_departure;
        cin >> airport_departure;

        cout << "airport of arrival: ";
        string airport_arrival;
        cin >> airport_arrival;

        cout << "standard price for one passenger: ";
        int price;
        cin >> price;

        cout << "first class ((y)es or (n)o): ";
        string is_first_class;
        bool is_first_class_bool;
        cin >> is_first_class;
        while (true) {
            if (is_first_class == "y" || is_first_class == "n") {
                break;
            }
            else {
                cout << "Wrong input! Input again: ";
                cin >> is_first_class;
            }
        }
        if (is_first_class == "y") {
            is_first_class_bool = true;
        }
        else {
            is_first_class_bool = false;
        }

        Flight* flight = new Flight(departure, flight_code, airport_departure, airport_arrival, price, is_first_class_bool, true);
        return flight;
    }
    else if (user_input == "2") {
        cout << "code of train: ";
        string train_code;
        cin >> train_code;

        cout << "main train station of departure: ";
        string trainstation_departure;
        cin >> trainstation_departure;

        cout << "main train station of arrival: ";
        string trainstation_arrival;
        cin >> trainstation_arrival;

        cout << "first class ((y)es or (n)o): ";
        string is_first_class;
        bool is_first_class_bool;
        cin >> is_first_class;
        while (true) {
            if (is_first_class == "y" || is_first_class == "n") {
                break;
            }
            else {
                cout << "Wrong input! Input again: ";
                cin >> is_first_class;
            }
        }
        if (is_first_class == "y") {
            is_first_class_bool = true;
        }
        else {
            is_first_class_bool = false;
        }

        cout << "price for one passenger: ";
        int price;
        cin >> price;

        Train* train = new Train(departure, train_code, trainstation_departure, trainstation_arrival, price, is_first_class_bool);
        return(train);
    }
}

int Request::lastNo = 1;

//Main
int main()
{
    CallCenter call_center;

    Accomodation* accomodation_list;
    Request* request_list;
    string input;

    Transport* outward_transport;
    Transport* return_transport;

    while (true) {
        cout << "CALL CENTER BOOKING REQUEST " << endl;
        cout << "0 end" << endl;
        cout << "1 new reservation request standard " << endl;
        cout << "2 new reservation request superior " << endl;
        cout << "3 show reservation request" << endl;
        cout << "4 show all reservation requests" << endl;
        cout << "your choice:  ";
        cin >> input;

        while (true) {
            if (input == "0" || input == "1" || input == "2" || input == "3" || input == "4") {
                break;
            }
            cout << "Wrong input! Input again: ";
            cin >> input;
        }

        if (input == "0") {
            break;
        }
        else if (input == "1") {
            accomodation_list = new Accomodation(80, 150,10);
            accomodation_list->ask_data();

            cout << "please choose transport outward: " << endl;
            outward_transport = inputTransport(accomodation_list->getCheckInDate());

            cout << "please choose transport return: " << endl;
            return_transport = inputTransport(accomodation_list->getCheckInDate());

            request_list = new Request(accomodation_list, nullptr, outward_transport, return_transport);
            call_center.append(request_list);
        }
        else if (input == "2") {
            accomodation_list = new Accomodation(110, 210, 10);
            accomodation_list->ask_data();

            cout << "please choose transport outward: " << endl;
            outward_transport = inputTransport(accomodation_list->getCheckInDate());

            cout << "please choose transport return: " << endl;
            return_transport = inputTransport(accomodation_list->getCheckInDate());

            request_list = new Request(accomodation_list, nullptr, outward_transport, return_transport);
            call_center.append(request_list);
        }
        else if (input == "3") {
            int request_no;
            cout << "number of reservation request: ";
            cin >> request_no;
            while (request_no < 1) {
                cout << "Please enter a valid value: ";
                cin >> request_no;
            }
            Request* request_delete = call_center.getRequest(request_no);
            if (request_delete != NULL) {
                request_delete->print();
                cout << "(c)ancel this request or (n)ot: ";
                string cancel_input;
                cin >> cancel_input;
                while (true) {
                    if (cancel_input == "c" || cancel_input == "n") {
                        break;
                    }
                    cout << "Please enter a valid value: ";
                    cin >> cancel_input;
                }
                if (cancel_input == "c") {
                    call_center.cancel(request_delete);
                    delete(request_delete);
                }
            }
        }
        else if (input == "4") {
            call_center.print_all();
        }
    }

    return 0;
}
