#include <iostream>
#include <string>
using namespace std;

const int ROWS = 5;
const int COLS = 2;
const int NUM_ROWS = 9;
const int NUM_SEATS = 6;
float flightTimes[ROWS][COLS] = {{7.00, 9.30}, {9.00, 11.30}, {11.00,13.30}, {13.00, 15.30}, {15.00, 17.30}};
const float ECONO_CLASS = 1600.00;
const int MAX_BOOKINGS = 10;

struct FlightDetails
{
    string name;
    float departTime;
    float arriveTime;
    string seatNum;
    float price;
    string travelClass;
};

void displayTimeMenu(int &timeOptionP)
{
    for(int j = 0; j < COLS - 1; j++)
        cout << '\t'<< "Depart" << '\t' << "Arrive" << endl;

    for(int i = 0; i < ROWS; i++)
    {
        cout << i + 1 << ".";
        for(int j = 0; j < COLS; j++)
            cout << '\t' << flightTimes[i][j];
        cout << endl;
    }


    cout << endl << "Choose the time by entering the option number from the displayed list: " << endl;
    cin >> timeOptionP;

    while(timeOptionP > 5 || timeOptionP <= 0)
    {
        cout << "Incorrect option! Please choose from 1 - 5." << endl;
        cin >> timeOptionP;
    }

}

void displaySeatingArrangement(const string planP[][NUM_SEATS])
{
    char row = 'A';
    int col = 1;
    string sNo;
    double firstClass = (ECONO_CLASS * 20 / 100) + ECONO_CLASS;
    int walkway =  0;

    for(int i = 0; i < NUM_ROWS; i++)
    {
        if(i == 0)
            cout << "First class(" << firstClass << ")" << endl;

        cout << "|" ;

        if(i % 4 == 0  && i / 4 == 1)
        {
            cout << "Economy class(" <<ECONO_CLASS <<  ")"<< endl <<  "|";
        }


        for(int j = 1; j <= NUM_SEATS; j++)
        {
            sNo = "";
            sNo += row;
            sNo += to_string(col);

            if((i != 8 || j != 2) && (i != 8 || j != 3) && (i != 8 || j != 4) && (i != 8 || j != 5) )
            {
                cout << sNo;
                col++;
                cout << "|";

                 if(j % 3 == 0 )
            {

                if(walkway == 0)
                {
                    if(i != 8 )
                    {
                        cout << "----|";
                        walkway = 1;
                    }
                }

                else
                {
                    walkway = 0;
                    col = 1;
                }
            }

            }


        }
         row += 1;

        cout << endl;
    }

}

bool seatValidation(FlightDetails bookingP[], string seatNumberP, int timeOptionP)
{
    float departure = flightTimes[timeOptionP - 1][0];
    bool isBooked = false;
    string bookedSeat;
    int i = 0;

    while( i < MAX_BOOKINGS)
    {

            if(bookingP[i].seatNum == seatNumberP && bookingP[i].departTime == departure)
            {
                isBooked = true;
                break;
            }
            else
            {
                isBooked = false;
            }
        i++;
    }
    return isBooked;
}


void displaySeatingArrangement2(FlightDetails bookingP[], string seatNumberP, int timeOptionP)
{
    char row = 'A';
    int col = 1;
    string sNo;
    double firstClass = (ECONO_CLASS * 20 / 100) + ECONO_CLASS;
    int walkway =  0;
    bool isBooked;

    for(int i = 0; i < NUM_ROWS; i++)
    {
        if(i == 0)
            cout << "First class(" << firstClass << ")" << endl;

        cout << "|" ;

        if(i % 4 == 0  && i / 4 == 1)
        {
            cout << "Economy class(" <<ECONO_CLASS <<  ")"<< endl <<  "|";

        }

        for(int j = 1; j <= NUM_SEATS; j++)
        {
            sNo = "";
            sNo += row;
            sNo += to_string(col);
            isBooked = seatValidation(bookingP, sNo, timeOptionP);

            if((i != 8 || j != 2) && (i != 8 || j != 3) && (i != 8 || j != 4) && (i != 8 || j != 5))
            {
                col++;
                if(isBooked == true)
                {
                    sNo = "**";
                    cout << sNo;

                }
                else
                {
                    cout << sNo;

                }

                cout << "|";

                 if(j % 3 == 0 )
                {
                    if(walkway == 0)
                    {
                        if(i != 8 )
                        {
                            cout << "----|";
                            walkway = 1;
                        }

                    }

                    else
                    {
                        walkway = 0;
                        col = 1;
                    }
            }

            }


        }
         row += 1;
        cout << endl;
    }

}
double calcTicketPrice(FlightDetails bookingP)
{
    if((bookingP.seatNum.substr(0.1)) > "D")
        bookingP.price = ECONO_CLASS;
    else
        bookingP.price = (ECONO_CLASS * 20/ 100) + ECONO_CLASS;

    return bookingP.price;
}

void displayTicket(FlightDetails & bookingP)
{
    if((bookingP.seatNum.substr(0,1)) > "D")
        bookingP.travelClass = "Economy class";
    else
        bookingP.travelClass = "First class";

    cout << "*************************" << endl;
    cout << "Travel tikcet for Flight" << endl;
    cout << "*************************" << endl;
    cout << "Name" << '\t'  << '\t' << ": " << bookingP.name;
    cout << '\t' << '\t' << "Travel Ticket Class" << '\t' << ": " << bookingP.travelClass << endl;
    cout << '\t' << '\t' << '\t' << '\t' << '\t' << "Seat No" <<  '\t'<< '\t' << '\t' << ": " << bookingP.seatNum << endl;
    cout << "Departure " << '\t' << ": " << "Johannesburg" << '\t' << '\t' << "Departure Time " << '\t'<< '\t' << ": "  << bookingP.departTime << endl;
    cout << "Destination " << '\t' << ": " << "Cape Town" << '\t' << '\t' << "Arrival Time " << '\t'<< '\t' <<": " << bookingP.arriveTime << endl;
    cout << "*************************" << endl;
    cout << "Amount: R" << calcTicketPrice(bookingP);
    cout << " Thank you for booking with COS1511. Your travel agent for queries is Annie Mathew." << endl;
    cout << "*************************" << endl;

}

int main()
{
    string fullName;
    int timeOption;
    float departureTime;
    int timeCounter, timeCounter1, timeCounter2, timeCounter3, timeCounter4, timeCounter5;
    timeCounter1 = timeCounter2 = timeCounter3 = timeCounter4 = timeCounter5 = 0;
    string plan[NUM_ROWS][NUM_SEATS];
    string seatNumber;
    FlightDetails booking[MAX_BOOKINGS];
    bool validBooking;
    int i = 0;
    char input;

    do
    {
         cout << "Welcome to COS1511 Flight Booking System" << endl << endl;
        cout << "Enter full name: " << endl;
        getline(cin, fullName, '\n');
        cout << endl;
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout.precision(2);
        cout << "The availale travel times for flights are: " << endl;
        displayTimeMenu(timeOption);

        cout << "The available seats for " << flightTimes[timeOption - 1][0] << " are as follows: " << endl;
        switch(timeOption)
        {
        case 1:
            timeCounter = timeCounter1;
            break;
        case 2:
            timeCounter = timeCounter2;
            break;
        case 3:
            timeCounter = timeCounter3;
            break;
        case 4:
            timeCounter = timeCounter4;
            break;
        case 5:
            timeCounter = timeCounter5;
            break;
        }

        if(timeCounter == 0)
        {
            displaySeatingArrangement(plan);
            cout << endl << "Please key in a seat number to choose a seat(eg:A2)" << endl;
        }
        else
        {
            displaySeatingArrangement2(booking, seatNumber, timeOption);
            cout << endl << "Please note seats already taken are indicated with an asterisk." << endl;
            cout << "Please key in a seat number to choose a seat(eg:A2)" << endl;

        }

        do
        {
            cin >> seatNumber;
            if((seatValidation(booking, seatNumber, timeOption)))
           {
                   cout << "Sorry, the seat is taken" << endl;
                   cout << "Please choose a seat that is available." << endl;
            }

        }while((seatValidation(booking, seatNumber, timeOption)));

        booking[i].name = fullName;

        if((seatNumber.substr(0,1)) == "D")
            booking[i].travelClass = "Economy class";
        else
            booking[i].travelClass = "First class";

        booking[i].departTime = flightTimes[timeOption -1][0];
        booking[i].arriveTime = flightTimes[timeOption - 1][1];
        booking[i].seatNum = seatNumber;

        displayTicket(booking[i]);
        i++;

        cout << "Do you want to make another booking(Y/N)?" << endl;
        cin >> input;
        cin.get();
        if(timeOption == 1)
            timeCounter1++;
        else if(timeOption == 2)
            timeCounter2++;
        else if(timeOption == 3)
            timeCounter3++;
        else if(timeOption == 4)
            timeCounter4++;
        else if(timeOption == 5)
            timeCounter5++;

    }while(toupper(input) == 'Y');
    cout << endl;

    cout << "Number of bookings for " << flightTimes[0][0] << " a.m : " << timeCounter1 << endl;
    cout << "Number of bookings for " << flightTimes[1][0] << " a.m : " << timeCounter2 << endl;
    cout << "Number of bookings for " << flightTimes[2][0] << " a.m : " << timeCounter3 << endl;
    cout << "Number of bookings for " << flightTimes[3][0] << " p.m : " << timeCounter4 << endl;
    cout << "Number of bookings for " << flightTimes[4][0] << " p.m : " << timeCounter5 << endl;

    return 0;
}
