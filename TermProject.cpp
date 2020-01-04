#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <iomanip>

using namespace std;

class Person
{
private:
	string name;
	string PN;

public:
	string getName() { return name; }; //Person 클래스의 member variable name을 반환
	string getPN() { return PN; };
}; //Person 클래스의 member variable PN을 반환

class Student : public Person
{
public:
	string s_name;
	string s_ID;

	Student(string name, string ID)
	{
		s_name = name;
		s_ID = ID;
	} //Student 클래스의 member variable 초기화
	~Student() {};

	string getS_ID()
	{
		cout << "Student ID: " << s_ID;
		return s_ID;
	}
}; //Student 클래스의 member variable s_ID 출력과 반환

class Professor : public Person
{
public:
	Professor(string name, string E_ID) :
		f_name{ name },
		f_ID{ E_ID }
	{
	} //Professor 클래스의 member variable 초기화
	string f_name;
	string f_ID;
	string getf_ID()
	{
		cout << "Professor: " << f_ID;
		return f_ID;
	}
}; //Professor 클래스의 member variable f_ID 출력과 반환


class Club
{
public:
	string c_type;
	vector<string> member_list; // 동아리에 소속된 학생들의 학번 list 
	string c_name;

	//Constructor & Destructor
	Club(string name, string type) :
		c_name{ name },
		c_type(type)
	{
	}
	Club() :
		c_name{ " " },
		c_type(" ")
	{
	}//default 값으로 초기화

	~Club()
	{
	}

	Club operator=(Club c)
	{
		c_name = c.c_name;
		c_type = c.c_type;
		member_list = c.member_list;
		return *this;
	}//operator overloading

	void AddMember(Student s)
	{
		auto result = find(begin(member_list), end(member_list), s.s_ID);
		if (result == end(member_list))
		{
			cout << this->c_name << "에 " << s.s_name << " 가입.\n";
			member_list.push_back(s.s_ID);
		}
		else
		{
			cout << "You are already in the member of club list." << endl;
		}
	};

	void AddMember(Professor f)
	{
		auto result = find(begin(member_list), end(member_list), f.f_ID);
		if (result == end(member_list))
		{
			cout << this->c_name << "에 " << f.f_name << " 가입.\n";
			member_list.push_back(f.f_ID);
		}
		else {
			cout << "You are already in the member of club list." << endl;
		}
	};

	//member_list에 name이 있으면 true, 없으면 false return.
	bool CheckMember(string ID)
	{
		auto result = find(begin(member_list), end(member_list), ID);
		if (result != end(member_list))
		{
			cout << "You are member of Club." << endl;
			return true;
		}
		else
		{
			cout << "You are not member of Club." << endl;
			return false;
		}
	};

	// (string)c_name 출력 후 return
	string GetClubName()
	{
		cout << "Club name is " << c_name << "." << endl;
		return c_name;
	}

	// (vector<string>)member_list 출력 후 return
	vector<string> GetMemberList()
	{
		std::cout << "Member List: [ ";
		for (auto& m : member_list)
		{
			cout << m << " ";
		}
		cout << "]\n";
		return member_list;
	}

	// (string)c_type 출력 후 return
	string GetType()
	{
		std::cout << c_name << "'s Type is " << c_type << "." << std::endl;
		return c_type;
	}

};

class MultiR // 원하는 공용공간 예약 및 취소를 위한 class
{
private:
	int room_number;
	vector<string> reservation_time{ 24, "o" }; // 공용공간 예약시간(0시~23시)을 위해 "o"으로 채워진 24개의 vector를 만든다.
public:
	int r_type = 1;
	MultiR() :
		MultiR(0)
	{
	}
	MultiR(int num)
	{
		room_number = num;
	}
	~MultiR() // MultiR() destructor
	{
	}

	void reservation(int starting_time, int term) // 공용공간 예약을 위해 사용을 원하는 시작 시간과, 얼마 동안 사용을 원하는지를 입력받는다.
	{
		int a = 0;
		for (vector<string>::iterator it = reservation_time.begin() + starting_time; it != reservation_time.begin() + starting_time + term; it++) // 원하는 사용 시작시간부터 (시작시간+사용시간)까지 "o"가 있으면 이미 예약이 찼음을 알려주고 break한다.
		{
			if (*it != "o")
			{
				a = 1;
				cout << "There are already booked up. Reservation failed." << endl;
				break;
			}
		}
		if (a == 0) // 원하는 사용 시작시간부터 (시작시간+사용시간)까지 "o"가 없다면, 예약이 성공적으로 완료되었음을 알려주고, 해당된 시간에 적혀있는 "o"를 "x"로 바꿔준다.
		{
			cout << "Reservation is successfully completed!\nThank you for using the Biseul Changui Yunghapgwan!" << endl;
			replace(this->reservation_time.begin() + starting_time, this->reservation_time.begin() + starting_time + term, "o", "x");
		}
	}

	void cancel_reservation(int starting_time, int term) // 공용공간 취소 시 사용
	{
		int a = 0;
		for (vector<string>::iterator it = reservation_time.begin() + starting_time; it != reservation_time.begin() + starting_time + term; it++) // 취소를 원하는 시간부터 (취소 시작시간+취소기간)까지 "x"가 없다면, 기존에 예약이 되어있지 않아 취소를 할 수 없다고 알려주고 break한다. 
		{
			if (*it != "x")
			{
				a = 1;
				cout << "There are no reservation. Cancellation failed." << endl;
				break;
			}
		}
		if (a == 0) // 취소를 원하는 시간부터 (취소 시작시간+취소기간)까지 "x"가 있다면, 취소가 성공적으로 완료되었음을 알려주고, 해당된 시간에 적혀있는 "x"를 "o"로 바꿔준다.
		{
			cout << "Cancellation is successfully completed!\nThank you for using the Biseul Changui Yunghapgwan!" << endl;
			replace(this->reservation_time.begin() + starting_time, this->reservation_time.begin() + starting_time + term, "x", "o");
		}
	}

	void ShowTime() // 0부터 23시까지 각 시간 별로 예약이 차있는지 아닌지 한번에 확인할 수 있게 예약현황을 보여준다.
	{
		cout << "(Hour)            | ";
		for (int i = 0; i < 24; i++)
		{
			cout << " " << i << " ";
		}
		cout << endl;
		cout << "------------------------------------------------------------------------------------------------------------" << endl;
		cout << "(Availability)    | ";
		for (int i = 0; i < 24; i++)
		{
			if (i <= 10)
				cout << " " << reservation_time[i] << " ";
			if (i > 10)
				cout << "  " << reservation_time[i] << " ";
		}
	}
	void description() // chair와 desk는 모든 방에서 사용할 수 있기 때문에 대여가능함을 알려준다.
	{
		cout << "You can use chair and desk." << endl;
	}
};

class Mirror : public MultiR // MuliR을 상속받는 Mirror 
{
private:
	int r_type = 2;
public:
	void description() // Mirror 예약 시 amp, speaker를 대여할 수 있음을 알려준다.
	{
		cout << "You can also use amp, speaker." << endl;
	}
};

class Studio : public MultiR //MultiR을 상속받는 Studio 
{
private:
	int r_type = 3;
public:
	void description() // Studio 예약 시 mic, recording machine, computer를 대여할 수 있음을 알려준다.
	{
		cout << "You can also use mic, recording machine, computer." << endl;
	}
};

class Stage : public MultiR //MultiR을 상속받는 Stage 
{
private:
	int r_type = 4;
public:
	void description() // Stage 예약 시 light, amp, mic를 대여할 수 있음을 알려준다.
	{
		cout << "You can also use light, amp, mic." << endl;
	}
};

Club find_club(string c_name, vector<Club> clubs) // 입력받은 동아리가 시스템에 등록되어있는 동아리인지 확인한다.
{
	Club none;
	for (vector<Club>::iterator it = clubs.begin(); it != clubs.end(); it++) // clubs vector의 처음부터 끝까지 입력받은 동아리가 들어있는지 그 여부를 확인한다.
	{
		if ((*it).c_name == c_name)
			return *it;
	}
	return none;
}

void AvailableRoom(Club c) // 입력받은 동아리의 type별로 사용 가능한 공용공간이 무엇인지 알려준다. 
{
	if (c.c_type == "music")
		cout << c.c_name << " can use Mirror, Multi Room, Studio, Stage." << endl;

	if (c.c_type == "dance")
		cout << c.c_name << " can use Mirror, Multi Room, Stage. " << endl;

	if (c.c_type == "acting")
		cout << c.c_name << " can use Stage, Multi Room." << endl;

	if (c.c_type == "default")
		cout << c.c_name << " can use Multi Room." << endl;
}

bool CheckClubRoom(Club c, int a) //예약시 입력한 방 타입이 해당 동아리에서 이용할 수 있는 타입인지를 확인한 후, true/false 반환
{
	if (c.c_type == "music")
		return true;

	if (c.c_type == "dance")
	{
		if (a == 1)
			return true;
		else if (a == 2)
			return true;
		else if (a == 4)
			return true;
		else
			return false;
	}
	if (c.c_type == "acting")
	{
		if (a == 1)
			return true;
		else if (a == 4)
			return true;
		else
			return false;
	}
	if (c.c_type == "default")
	{
		if (a == 1)
			return true;
		else
			return false;
	}
}

void ShowClubs(vector<Club>clubs) // 현재 vector<Club> clubs에 존재하는 모든 동아리를 보여준다.(예약시 동아리 이름을 헷갈리지 않도록 화면에 출력해줌)
{
	cout << endl << "Current Existing Clubs" << endl;
	cout << " |  ";
	for (vector<Club>::iterator iter = begin(clubs); iter != end(clubs); ++iter)
	{
		cout << (*iter).c_name << "  |   ";
	}
	cout << endl;
}

int main()
{
	//등록
	vector<Club> clubs;
	Club c1("BGM", "dance");
	Club c2("VOICEFISHING", "music");
	Club c3("AMARU", "music");
	Club c4(".AVI", "acting");
	Club c5("BISLATE", "acting");
	Club c6("DGROID", "default");
	Club c7("DGISTWHALES", "default");
	Club c8("THECUE", "default");
	Club c9("Professor", "music");
	Student s1("이구", "201811118");
	Student s2("이지수", "201811143");
	Student s3("서은빈", "201812345");
	Student s4("박준용", "201812346");
	Student s5("김별", "201811024");
	Student s6("김달", "201811056");
	Student s7("박하늘", "201811097");
	Student s8("박구름", "201811058");
	Student s9("정디지", "201811150");
	Student s10("정스트", "201811163");
	Professor f1("신동훈", "1");
	c1.AddMember(s1);
	c1.AddMember(s3);
	c2.AddMember(s5);
	c3.AddMember(s4);
	c3.AddMember(s9);
	c4.AddMember(s6);
	c5.AddMember(s7);
	c6.AddMember(s2);
	c6.AddMember(s3);
	c7.AddMember(s1);
	c7.AddMember(s10);
	c8.AddMember(s8);
	c8.AddMember(s9);
	c9.AddMember(f1);

	clubs.push_back(c1);
	clubs.push_back(c2);
	clubs.push_back(c3);
	clubs.push_back(c4);
	clubs.push_back(c5);
	clubs.push_back(c6);
	clubs.push_back(c7);
	clubs.push_back(c8);
	clubs.push_back(c9);

	// 실행
	int ReserveOrCancle;
	string rID;
	string rc_name;
	int rtype;
	string check;
	int starting_time;
	int term;
	bool check_rtype;
	Club CurrentClub;
	bool CheckResult;

	MultiR Multi;
	Mirror Mirror;
	Studio Studio;
	Stage Stage;

	while (true) {
		cout << "Welcome to Biseul Changui Yunghapgwan reservation system! Select Menu. \n 1. Reservation\n 2. Reservation Cancellation\n 3. Exit" << endl;
		cin >> ReserveOrCancle;
		switch (ReserveOrCancle) //1. 예약, 2. 예약취소, 3. 프로그램 종료 중 선택
		{
		case 1:
			cout << "You select reservation" << endl;
			cout << "Please enter your Student ID or Employee ID." << endl; // 학번 or 사번 입력
			cin >> rID;
			ShowClubs(clubs);
			cout << "Please enter your Club name. If you are Professor, enter 'Professor'." << endl; // 동아리 이름 입력
			cin >> rc_name;
			CurrentClub = find_club(rc_name, clubs); // 입력받은 동아리 이름을 이용해 Club 객체 찾음
			CheckResult = CurrentClub.CheckMember(rID); // 해당 학번이 입력받은 동아리의 member list에 존재하는지 확인.
			if (CheckResult == false)
			{
				cout << "Reservation Failed." << endl;
				cout << endl;
				continue;
			}

			cout << "What type of Room do you want to reserve? " << endl; //예약할 방의 종류 선택
			AvailableRoom(CurrentClub); // 해당 동아리가 사용할 수 있는 방의 종류를 화면에 출력
			cout << "1. Multi\n" << "2. Mirror\n" << "3. Studio\n" << "4. Stage\n";
			cin >> rtype;
			check_rtype = CheckClubRoom(CurrentClub, rtype); //사용할 수 있는 타입의 방을 선택했는지 확인
			if (check_rtype == false)
			{
				cout << "You can't use this type of room. Reservation Failed." << endl;
				cout << endl;
				continue;
			}

			switch (rtype) // 사용을 선택한 방의 예약 현황 화면에 출력
			{
			case 1:
				Multi.ShowTime();
				break;
			case 2:
				Mirror.ShowTime();
				break;
			case 3:
				Studio.ShowTime();
				break;
			case 4:
				Stage.ShowTime();
				break;
			};

			//방 사용 시작시간을 입력 받음.
			cout << "\nWhen do you start using room? (0 ~ 23)";
			cin >> starting_time;
			if (starting_time > 23 || starting_time < 0) {
				cout << "Invalid time. Reservation failed." << endl;
				continue;
			}
			//방 사용 시간을 입력 받음.
			cout << "How long do you want to use room? (equal or less than 4!)";
			cin >> term;
			if (term > 4) {
				cout << "It can't be used for more than four hours. Reservation failed." << endl;
				continue;
			}
			//입력한 동아리 정보, 선택한 room type, 사용 시작 시간, 사용 시간을 확인시킴. 그리고 각 방마다 description을 보여줌.
			cout << "Your club is " << CurrentClub.c_name << "." << "You select the Room type " << rtype << ". Start using at " << starting_time << " for " << term << " hours.";
			switch (rtype)
			{
			case 1:
				Multi.description();
				break;
			case 2:
				Mirror.description();
				Multi.description();
				break;
			case 3:
				Studio.description();
				Multi.description();
				break;
			case 4:
				Stage.description();
				Multi.description();
				break;
			};
			// 방 대여에 대해 다시 물음.
			cout << "Are you sure? (select Y or N)" << endl;
			cin >> check;
			if (check != "Y")
			{
				cout << "Try Again!" << endl;
				break;
			}

			// 방 대여에 대한 확답을 받고 난 후 starting_time부터 term동안 방의 reservation time을 o에서 x로 바꿔줌.
			switch (rtype)
			{
			case 1:
				Multi.reservation(starting_time, term);
				break;
			case 2:
				Mirror.reservation(starting_time, term);
				break;
			case 3:
				Studio.reservation(starting_time, term);
				break;
			case 4:
				Stage.reservation(starting_time, term);
				break;
			};
			break;
			// 취소할 경우의 case
		case 2:
			cout << "You select reservation cancellation" << endl;
			//student ID 나 Employ ID를 입력 받음.
			cout << "Please enter your Student ID or Employ ID" << endl;
			cin >> rID;
			// 현재 등록되어있는 동아리 목록을 보여주고 동아리 이름을 입력받음.
			ShowClubs(clubs);
			cout << "Please enter your Club name. If you are Professor, enter 'Professor'." << endl;
			cin >> rc_name;
			// 동아리 이름만으로 그 동아리를 복사해온 후 동아리 내부 동아리원 vector member list에 있는지 확인함. 없을 시 취소가 불가능.
			CurrentClub = find_club(rc_name, clubs);
			CheckResult = CurrentClub.CheckMember(rID);
			if (CheckResult == false)
			{
				cout << "Cancellation Failed." << endl;
				cout << endl;
				continue;
			}
			// 동아리에 따라 어떤 type의 방을 취소할 것인지 선택받음. type은 동아리의 특징마다 결정되어 있으며, 동아리의 특징에 맞지 않는 경우 취소가 불가능.
			cout << "What type of Room do you want to cancel reservation? " << endl;
			AvailableRoom(CurrentClub);
			cout << "1. Multi\n" << "2. Mirror\n" << "3. Studio\n" << "4. Stage\n";
			cin >> rtype;
			check_rtype = CheckClubRoom(CurrentClub, rtype);
			if (check_rtype == false)
			{
				cout << "You can't cancel this type of room. Cancellation Failed." << endl;
				cout << endl;
				continue;
			}
			// 현재 그 방의 대여 시간을 보여준다.
			switch (rtype) {
			case 1:
				Multi.ShowTime();
				break;
			case 2:
				Mirror.ShowTime();
				break;
			case 3:
				Studio.ShowTime();
				break;
			case 4:
				Stage.ShowTime();
				break;
			};
			// 선택했던 starting time을 입력받음.
			cout << "\nWhen did you select the starting time? (0 ~ 23)";
			cin >> starting_time;
			if (starting_time > 23 || starting_time < 0)
			{
				cout << "Invalid time. Cancellation failed." << endl;
				continue;
			}
			// 예약했던 term을 입력받음.
			cout << "How many hours did you reserve to use room? (equal or less than 4!)";
			cin >> term;
			if (term > 4)
			{
				cout << "It can't be reserved for more than four hours. Cancellation failed." << endl;
				continue;
			}
			// club 이름, 선택했던 starting_time, term을 보여줌. 다시 물으며 확답을 얻음.
			cout << "Your club is " << CurrentClub.c_name << "." << "You selected the Room type " << rtype << ". Start using at " << starting_time << " for " << term << " hours.";
			cout << "Are you sure? (select Y or N)" << endl;
			cin >> check;
			if (check != "Y")
			{
				cout << "Try Again!" << endl;
				break;
			}
			// 확답에 대해서 선택한 방의 starting_time부터, term 동안 x를 o로 바꾸어줌.
			switch (rtype)
			{
			case 1:
				Multi.cancel_reservation(starting_time, term);
				break;
			case 2:
				Mirror.cancel_reservation(starting_time, term);
				break;
			case 3:
				Studio.cancel_reservation(starting_time, term);
				break;
			case 4:
				Stage.cancel_reservation(starting_time, term);
				break;
			};
			break;
		case 3:
			return 0;
		};
	}
}