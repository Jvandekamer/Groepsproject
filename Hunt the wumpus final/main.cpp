#include <iostream>
#include <vector>
#include "animations.h"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;


void animatetext(string text){ // Deze functie gebruik ik om de tekst op een leuke manier op het scherm te zetten // deze functie is gemaakt door Jeff
	for(unsigned int i = 0;i < text.length();i++){
		cout << text.at(i);
		this_thread::sleep_for(chrono::milliseconds(18));
	}
}


void read_stats_file () { // deze functie is gemaakt door Adam
	string line; 
	ifstream myfile("statistics.txt"); 
	if (myfile.is_open()){ 
		while(getline(myfile,line)){
			animatetext(line + "\n");
		}
	}
}


void make_statistic_file(int moves, int batgrabs, string cause_of_death, int missed_shots, bool wumpus_killed, bool normalmode){ // Deze functie is gemaakt door Adam
	ofstream myfile; 
	if(normalmode){
		myfile.open("statistics.txt");
	}
	else{
		myfile.open("statistics.txt", ofstream::app);
	}
	myfile << "Moves: " << moves <<"\n";
    myfile << "Bats grabs: " << batgrabs <<"\n";
	myfile << "Cause of death: " << cause_of_death <<"\n";
	myfile << "Missed_shots: " << missed_shots <<"\n";
	if(wumpus_killed){
		myfile << "Wumpus killed: Yes\n";
	}
	else{
		myfile << "Wumpus killed: No\n\n\n";
	}
    myfile.close(); 
}


void replay(vector<vector<int>> & map){ // deze functie is gemaakt door Adam
	// Dit is alleen om de map uit te printen 
	for(unsigned int i=0; i<map.size(); i++){
		//cout << "Room " << i+1 << " is connected with: ";
		animatetext(("Room " + to_string(i+1)+" is connected with: "));
		for(unsigned int j=0; j<map[i].size(); j++){
			cout << map[i][j] << ", ";
		}
		cout << "\n";
	}
	cout << "\n";
}


void get_entities(int & wumpus, vector<int> & bats, vector<int> & pits ){ // deze Functie is gemaakt door Adam
	vector<int> full_rooms;
	int entity_amount = 0;
	wumpus = (rand() % 19 + 2);
	full_rooms.push_back(wumpus);
	while(entity_amount < 4){
		bool tempvalue = true;
		int temp = (rand() % 19 + 2);
		for(unsigned int i = 0; i < full_rooms.size(); i++){
			if(full_rooms[i] == temp){
				tempvalue = false;
				break;
			}
		}
		if(tempvalue && entity_amount < 2){
			bats.push_back(temp);
			full_rooms.push_back(temp);
			entity_amount++;
		}
		else if(tempvalue){
			pits.push_back(temp);
			full_rooms.push_back(temp);
			entity_amount++;
		}
	}
}


void game_Info(string logo_txt, string info_txt){ // Deze functie is gemaakt door Mark
    string line;
    ifstream logo_file (logo_txt);
    if(logo_file.is_open()){
        while (getline (logo_file, line)){
            cout << line << endl;
        }
        cout << endl;
        logo_file.close();
    }
    else{
        animatetext("Unable to open logo file \n");
    }
    
    string user_input;
    animatetext("WOULD YOU LIKE TO SEE THE INSTRUCTIONS? (Y/N) ");
    cin >> user_input;
    while(user_input != "Y" && user_input != "y" && user_input != "N" && user_input != "n"){
        animatetext("WOULD YOU LIKE TO SEE THE INSTRUCTIONS? (Y/N) ");
        cin >> user_input;
    }
    cout << endl;
    if(user_input == "Y" || user_input == "y"){
        ifstream info_text (info_txt);
        if(info_text.is_open()){
            vector<string> info_lines = {};
            while (getline (info_text, line)){
                info_lines.push_back(line);
            }
            info_text.close();
            for(unsigned int i = 0; i < info_lines.size(); i++){
               // cout << info_lines[i] << endl;
				animatetext((info_lines[i] + "\n"));
            }
        }
        else{
        animatetext("Unable to open info text file.");
        }
    }
}


int Checklocation(int Playerlocation, vector<vector<int>>Map, int wumpus, int Bat1, int Bat2, int traproom1, int traproom2 ){ // Deze functie is gemaakt door Jeff
	if(Playerlocation==wumpus){
		return 1;
	}
	else if(Playerlocation == Bat1 || Playerlocation == Bat2){
		return 2;
	}
	else if(Playerlocation == traproom1 || Playerlocation == traproom2){
		return 3;
	}
	// als er nieuwe elementen in het spel zet deze hier dan in met een else if statement
	else{ // dit betekend dat de kamer leeg is
		return 0;
	}
}


string checksurrounding(int Playerlocation, vector<vector<int>>Map, int wumpus, int Bat1, int Bat2, int traproom1, int traproom2){ // Deze functie is gemaakt door Jeff
	string Warning = "";
	bool wumpdetected = false; // variable die laat zien of de wumpus is gespot
	bool Batsdetected = false; // variabel dei alat zien of de bats zijn gesport
	bool trapdetected = false; // variable dat laat zien dat er een val in de buurt zit
	for(int i=0; i < Map[Playerlocation-1].size(); i++){ // hier check je voor de hazzards op 1 kamer afstand
		if(Map[Playerlocation-1][i]==wumpus && !wumpdetected){
			wumpdetected = true;
			Warning+="You smell something nearby.\n";
		}
		if((Map[Playerlocation-1][i]==Bat1 || Map[Playerlocation-1][i]==Bat2) && !Batsdetected){
			Batsdetected = true;
			Warning+="You can hear squeaks.\n";
		}
		if((Map[Playerlocation-1][i]==traproom1 || Map[Playerlocation-1][i] == traproom2) && !trapdetected){
			trapdetected = true;
			Warning+="You feel a draft nearby.\n";
		}
		// hier kan je de nieuwe hazzards toevoegen voor detectie
	}
	for(int j=0; j < Map[Playerlocation-1].size();j++){ // hier vergelijk je de kamers waar de speler heen kan met de kamers waar de wumpus heen kan dus check je op 2 kamers afstand voor de wumpus
		for(int k = 0; k < Map[wumpus-1].size();k++){
			if(!wumpdetected && Map[Playerlocation-1][j] == Map[wumpus-1][k]){
				Warning+="You smell something nearby.\n";
				return Warning; // breekt de loop eerder als hij als is detected zodat hij sneller klaar is
			}
		}
	}
	return Warning;
}


void player_action(int & Playerlocation,vector<vector<int>>Map,int & wumpus,vector<int>bats,vector<int>pits,int & arrowcount,bool normalmode){ // deze functie is gemaakt door Jeff
	string choice; // deze string word gebruikt om de keuze vast te leggen die de speler elke rond maakt
	// nu gaan we de vectoren met de bats en pits splitsen zodat we ze wakkelijker kunnen vergelijken met de locatie van de speler
	int bat1 = bats[0];
	int bat2 = bats[1];
	int traproom1 = pits[0];
	int traproom2 = pits[1];
	int roomtoshootat; // deze bewaard de kamer waar de speler naar toe schiet
	
	int moves = 0; // dit is toegevoegd door adam voor statistieken
	int batgrabs = 0;
	string cause_of_death; 
	int missed_shots = 0; 
	bool wumpus_killed = false; 
	
	while(true){// Hier geven we de speler wat extra informatie over wat er zich in de kamers om hem heen bevint
		string Warning = checksurrounding(Playerlocation,Map,wumpus,bat1,bat2,traproom1,traproom2);
		if(Warning.size() > 0){
			animatetext(Warning);
			cout << endl;
		}
		animatetext(("You are currently in room: " + to_string(Playerlocation) + "\n"));
		animatetext("Connected rooms are: ");
		for(int i =0; i < Map[Playerlocation-1].size(); i++){
			cout << Map[Playerlocation-1][i] << " ";
			this_thread::sleep_for(chrono::milliseconds(20));
		}
		cout << endl;
		animatetext("Would you like to move or shoot? Enter M to move or S to shoot.\n");
		cin >> choice; // Hier laten we de speler de keuze maken of hij/zij wil bewegen of schieten
		while(!(choice == "M") && !(choice == "m") && !(choice == "s") && !(choice == "S")){
			animatetext("Invalid decision, please enter M to move or S to shoot.\n");
			cin >> choice;
		} 
		if(choice == "M" || choice == "m"){
			cout << endl;
			animatetext("Which room would you like to go to?\n");
			int tmp = Playerlocation; //tijdelijke variable om de vorige positie te bewaren
			cin >> Playerlocation;
			while(true){ //hier gebruik ik de tijdelijke variable om te checken of de kamer die je invult wel  te bereiken is vanaf die positie
				if(Playerlocation ==Map[tmp-1][0]){
					break;
				}
				if(Playerlocation ==Map[tmp-1][1]){
					break;
				}
				if(Playerlocation ==Map[tmp-1][2]){
					break;
				}
				animatetext("That room cannot be reached from my current position.\nWhich room would you like to go to?\n");
				cin >> Playerlocation;
			}
			moves++;
			cout << endl;
			//vanaf hier gaan we checken wat er in de huidge kamer zit, en wat daarvan het gevolg is
			int inhoud_huidige_kamer = Checklocation(Playerlocation, Map, wumpus, bat1, bat2, traproom1, traproom2); //geeft nul als de kamer leeg is, geeft 1 als er een wumpus in de kamer zit. Als er nieuwe elenten in het spel komen voeg die hier aan toe met een nieuwe int
			if(inhoud_huidige_kamer==1){
				cause_of_death = "Wumpus";
				make_statistic_file(moves, batgrabs, cause_of_death, missed_shots, wumpus_killed, normalmode);
				wumpus_eat_ani();
				animatetext("You were killed by the wumpus.\nGAME OVER\n");
				break; // deze breekt de loop en stopt dus het spel
			}
			else if(inhoud_huidige_kamer ==2){ // dit is wat er gebeurt als je in een bat kamer komt // dit onderdeel is gemaakt door Johny in samenwerking met Jeff
				batgrabs++;
				animatetext("You ran into a group of enraged bats.\n");
				int lastposition = Playerlocation;
				Playerlocation = rand() % 20 + 1;
				while(Playerlocation == wumpus || Playerlocation == lastposition){
					Playerlocation = rand() % 20 + 1;
				}
				animatetext(("The enraged bats picked you up and moved you to room: " + to_string(Playerlocation)+"\n" + "The enraged bats have returned to their room.\n"));
				cout << endl;
			} // einde van Batkamer onderdeel
			else if(inhoud_huidige_kamer ==3){ // Wat er gebeurd als je in een pit kamer komt 
				cause_of_death = "Bottomless pit";
				make_statistic_file(moves, batgrabs, cause_of_death, missed_shots, wumpus_killed, normalmode);
				pitt_fall_ani();
				animatetext("The room you entered in had no floor.\nYou fell down and died.\nGAME OVER.\n");
				break; // breekt de loop en stopt het spel
			}
			else{ // als de waarde niet een van de bovenstaande is dan mag de speler verder met spelen
				continue; 
			}
		}
		else{ // Dis is waar de speler uit komt in het geval dat hij besluit om te schieten // 
			animatetext(("You currently have " + to_string(arrowcount) + " arrows left.\nWhich room would you like to shoot at?\n"));
			cin >> roomtoshootat;
			while(!((roomtoshootat == Map[Playerlocation-1][0]) || (roomtoshootat == Map[Playerlocation-1][1]) || (roomtoshootat == Map[Playerlocation-1][2]))){
				animatetext("I cannot shoot at that room from my current position.\n");;
				cin >> roomtoshootat;
			}
			arrowcount-=1;
			cout << endl;
			if(roomtoshootat == wumpus){
				wumpus_killed = true;
				make_statistic_file(moves, batgrabs, cause_of_death, missed_shots, wumpus_killed, normalmode);
				kill_wumpus_ani();
				animatetext("You killed the wumpus.\nCongratulations you win!\n");
				break;
			}
			else{
				missed_shots++;
				animatetext("Your shot missed.\n");
				vector<int>possiblelocations={};
				for(unsigned int i2 = 0; i2 < 3;i2++){
					if(Map[wumpus-1][i2] != Playerlocation && Map[wumpus-1][i2] != bat1 && Map[wumpus-1][i2] != bat2 && Map[wumpus-1][i2] != traproom1 && Map[wumpus-1][i2] != traproom2 ){
						possiblelocations.push_back(Map[wumpus-1][i2]);
					}
				}
				if(possiblelocations.size() > 0){ // als het mogelijk is voor de wumpus om te verplaatsen
					animatetext("Your shot has allerted the wumpus.\nYou can hear movement.\n");
					if(possiblelocations.size() == 1){
						wumpus = possiblelocations[0];
					}
					else{
					int newroom = rand() % possiblelocations.size(); // genereerd een random waarde die kleiner is dan het aantal beschikbare kamers
					wumpus = possiblelocations[newroom];
					}
				}
			}
		}
		if(arrowcount <=0){
			empty_arrows_ani();
			animatetext("You ran out of arrows to kill the Wumpus with.\nGAME OVER.\n");
			cause_of_death = "No arrows left";
			make_statistic_file(moves, batgrabs, cause_of_death, missed_shots, wumpus_killed, normalmode);
			break; // kilt de speler
		}
	}
}


void robot_action(int & Playerlocation, vector<vector<int>>Map, int & wumpus, vector<int>Bats, vector<int>pits, int & arrowcount, bool normalmode, vector<int> & rooms_to_avoid, int & wumpusgevonden, bool & aiwin, vector<int> & inefficient_rooms){ // bijna hetzelfde als de player action functie, maar deze word door de AI bediend.
	string choice; // deze string word gebruikt om de keuze vast te leggen die de computer
	// nu gaan we de vectoren met de bats en pits splitsen zodat we ze wakkelijker kunnen vergelijken met de locatie van de speler
	int bat1 = Bats[0];
	int bat2 = Bats[1];
	int traproom1 = pits[0];
	int traproom2 = pits[1];
	int roomtoshootat; // deze bewaard de kamer waar de speler naar toe schiet
	
	int moves = 0;
	int batgrabs = 0; 
	string cause_of_death; 
	int missed_shots = 0; 
	bool wumpus_killed = false; 
	
	while(true){// Hier geven we de speler wat extra informatie over wat er zich in de kamers om hem heen bevint
		string Warning = checksurrounding(Playerlocation,Map,wumpus,bat1,bat2,traproom1,traproom2);
		if(Warning.size() > 0){
			animatetext(Warning);
			cout << endl;
		}
		animatetext(("You are currently in room: " + to_string(Playerlocation) + "\n"));
		animatetext("The connected rooms are: ");
		for(int i =0; i < Map[Playerlocation-1].size(); i++){
			cout << Map[Playerlocation-1][i] << " ";
			this_thread::sleep_for(chrono::milliseconds(20));
		}
		cout << endl;
		animatetext("Would you like to move or shoot? Enter M to move or S to shoot.\n"); // hier is een vraag
		
		if(wumpusgevonden != -1 && (wumpusgevonden == Map[Playerlocation-1][0] || wumpusgevonden == Map[Playerlocation-1][1] || wumpusgevonden == Map[Playerlocation-1][2])){
			animatetext("S\n"); // deze zorgt ervoor dat de speler kan zien wat de cpu kiest
			choice = "S"; // de computer speler schiet alleen als hij weet waar de wumpus zich bevind en hij die kamer kan zien.
		}
		else{// anders gaat de computer bewegen
			animatetext("M\n"); // deze zijn alleen om ervoor te zorgen dat de speler kan zien wat de cpu kiest
			choice = "M";
		}
		if(choice == "M" || choice == "m"){
			cout << endl;
			animatetext("Which room would you like to go to?\n");
			int tmp = Playerlocation; // nu moeten we bepalen wat de AI kiest
			// eerst kijk ik of er kamers zijn waar ik niet naartoe mag
			vector<int>roomsicanmoveto = {};
			vector<int>smartrooms = {};
			bool issafe;
			bool issmart;
			if(rooms_to_avoid.size() > 0){ // als er kamers zijn waar we niet naartoe mogen gaan we kijken of er een daarvan voor ons zit, en als dat zo is, dan zorgen we ervoor dat hij niet in de vector met roomsicanmoveto komt
				for(int j = 0; j < Map[Playerlocation-1].size();j++){
					issafe = true;
					for(int k = 0; k < rooms_to_avoid.size();k++){
						if(Map[Playerlocation-1][j] == rooms_to_avoid[k]){
							issafe = false;
						}
					}
					if(issafe == true){
						roomsicanmoveto.push_back(Map[Playerlocation-1][j]);
					}
				}
			}
			else{ // als er geen kamers zijn waar we niet naartoe mogen voegen we alle kamers waar we naar toe kunnen toe aan de vector
				for(int l = 0; l < Map[Playerlocation-1].size();l++){
					roomsicanmoveto.push_back(Map[Playerlocation-1][l]);
				}
			}
			// nu hebben we een vector met kamers die veilig zijn, dus gaan we nu kijken of er in die vector een kamer zit waar het slim is om naar toe te gaan(dus een kamer waar ik niet ben geweest)
			if(inefficient_rooms.size() > 0){
				for(int m = 0; m < roomsicanmoveto.size();m++){
					issmart=true;
					for(int n = 0; n < inefficient_rooms.size();n++){
						if(roomsicanmoveto[m] == inefficient_rooms[n]){
							issmart = false;
						}
					}
					if(issmart == true){
						smartrooms.push_back(roomsicanmoveto[m]);
					}
				}
			}
			if(smartrooms.size() > 0){ // als we kamers hebben waar het slim is om naar toe te gaan dan pikken we daar een random kamer uit
				Playerlocation = smartrooms[rand() % smartrooms.size()];
			}
			else{ // en als er geen kamers zijn die slim zijn om naar toe te bewegen dan pikken we gewoon een random kamer waar je naar toe kan
				Playerlocation = roomsicanmoveto[rand() % roomsicanmoveto.size()];
			}
			animatetext(to_string(Playerlocation));
			while(true){ //hier gebruik ik de tijdelijke variable om te checken of de kamer die je invult wel  te bereiken is vanaf die positie
				if(Playerlocation ==Map[tmp-1][0]){
					break;
				}
				if(Playerlocation ==Map[tmp-1][1]){
					break;
				}
				if(Playerlocation ==Map[tmp-1][2]){
					break;
				}
				animatetext("That room cannot be reached from my current position.\nWhich room would you like to go to?\n");
				Playerlocation = Map[Playerlocation-1][rand() % 3];
				animatetext(to_string(Playerlocation));
			}
			moves++;
			cout << endl;
			//vanaf hier gaan we checken wat er in de huidge kamer zit, en wat daarvan het gevolg is
			int inhoud_huidige_kamer = Checklocation(Playerlocation,Map,wumpus,bat1,bat2,traproom1,traproom2); //geeft nul als de kamer leeg is, geeft 1 als er een wumpus in de kamer zit. Als er nieuwe elenten in het spel komen voeg die hier aan toe met een nieuwe int
			if(inhoud_huidige_kamer==1){
				cause_of_death = "Wumpus";
				make_statistic_file(moves, batgrabs, cause_of_death, missed_shots, wumpus_killed,normalmode);
				wumpus_eat_ani();
				animatetext("You were killed by the wumpus.\nGAME OVER\n");
				rooms_to_avoid.push_back(Playerlocation); // dit leert de AI dat hij deze kamer niet binnen moet gaan
				if(arrowcount == 5){
					wumpusgevonden = Playerlocation; // dit leert de AI wat de wumpuslocatie in het spel is.
				}
				break; // deze breekt de loop en stopt dus het spel
			}
			else if(inhoud_huidige_kamer ==2){ // dit is wat er gebeurt als je in een bat kamer komt // dit onderdeel is gemaakt door Johny in samenwerking met Jeff
				batgrabs++;
				animatetext("You ran into a group of enraged bats.\n");
				int lastposition = Playerlocation;
				rooms_to_avoid.push_back(Playerlocation); // zorgt ervoor dat de AI leerd dat hij niet meer naar deze kamer moet gaan
				Playerlocation = rand() % 20 + 1;
				while(Playerlocation == wumpus || Playerlocation == lastposition){
					Playerlocation = rand() % 20 + 1;
				}
				animatetext(("The enraged bats picked you up and moved you to room: " + to_string(Playerlocation)+"\n" + "The enraged bats have returned to their room.\n"));
				cout << endl;
			} // einde van Batkamer onderdeel
			else if(inhoud_huidige_kamer ==3){ // Wat er gebeurd als je in een pit kamer komt 
				cause_of_death = "Bottomless pit";
				make_statistic_file(moves, batgrabs, cause_of_death, missed_shots, wumpus_killed, normalmode);
				rooms_to_avoid.push_back(Playerlocation);
				pitt_fall_ani();
				animatetext("The room you entered had no floor.\nYou fell down and died.\nGAME OVER.\n");
				break; // breekt de loop en stopt het spel
			}
			else{ // als de waarde niet een van de bovenstaande is dan mag de speler verder met spelen
				inefficient_rooms.push_back(Playerlocation);
				continue;
			}
		}
		else{ // Dis is waar de speler uit komt in het geval dat hij besluit om te schieten // 
			animatetext(("You currently have " + to_string(arrowcount) + " arrows left.\nWhich room would you like to shoot at?\n"));
			animatetext(to_string(wumpusgevonden));
			roomtoshootat = wumpusgevonden;
			while(!((roomtoshootat == Map[Playerlocation-1][0]) || (roomtoshootat == Map[Playerlocation-1][1]) || (roomtoshootat == Map[Playerlocation-1][2]))){
				animatetext("I cannot shoot at that room from my current position.\n");
				roomtoshootat = wumpusgevonden;
			}
			arrowcount-=1;
			cout << endl;
			if(roomtoshootat == wumpus){
				wumpus_killed = true;
				make_statistic_file(moves, batgrabs, cause_of_death, missed_shots, wumpus_killed, normalmode);
				kill_wumpus_ani();
				animatetext("You killed the wumpus.\nCongratulations you win!\n");
				aiwin = true;
				break;
			}
			else{
				missed_shots++;
				animatetext("Your shot missed.\n");
				vector<int>possiblelocations={};
				for(unsigned int i2 = 0; i2 < 3;i2++){
					if(Map[wumpus-1][i2] != Playerlocation && Map[wumpus-1][i2] != bat1 && Map[wumpus-1][i2] != bat2 && Map[wumpus-1][i2] != traproom1 && Map[wumpus-1][i2] != traproom2 ){
						possiblelocations.push_back(Map[wumpus-1][i2]);
					}
				}
				if(possiblelocations.size() > 0){ // als het mogelijk is voor de wumpus om te verplaatsen
					animatetext("Your shot has allerted the wumpus.\nYou can hear movement.\n");
					if(possiblelocations.size() == 1){
						wumpus = possiblelocations[0];
					}
					else{
					int newroom = rand() % possiblelocations.size(); // genereerd een random waarde die kleiner is dan het aantal beschikbare kamers
					wumpus = possiblelocations[newroom];
					}
				}
			}
		}
		if(arrowcount <=0){
			empty_arrows_ani();
			animatetext("You ran out of arrows to kill the wumpus with.\nGAME OVER.\n");
			cause_of_death = "No arrows left";
			make_statistic_file(moves, batgrabs, cause_of_death, missed_shots, wumpus_killed, normalmode);
			break; // kilt de speler
		}
	}
}


void make_map_file (vector<vector<int>> map, int wumpuslocation, vector<int> batslocation, vector<int> pitslocation) { // Gemaakt door adam
    ofstream myfile; 
    myfile.open("map.txt");
    for(unsigned int i=0; i<map.size(); i++){
        myfile << "room " << i+1 << "; ";
        for(unsigned int j=0; j<map[i].size(); j++){
            myfile << map[i][j] << ", ";
        }
        myfile << "\n";
    }
    myfile << "\nbats: ";
    for(unsigned int i=0; i<batslocation.size(); i++){
        myfile << batslocation[i] << ", ";
    }
    myfile << "\npits: ";
    for(unsigned int i=0; i<pitslocation.size(); i++){
        myfile << pitslocation[i] << ", ";
    }
    myfile << "\nwumpus: " << wumpuslocation << "\n";
    myfile.close(); 
}


vector<vector<int>> get_empty_map(int room_amount){ // Gemaakt door Adam
	// een een lege map een te maken, room_amount geeft aan hoeveel kamers de map bevat
	vector<vector<int>> Empty_map = {};
	for(int i=0; i<room_amount; i++){
		Empty_map.push_back({});
	}
	return Empty_map;
}


void read_config_file (vector<vector<int>> & map, int & wumpus, vector<int> & bats, vector<int> & pits) { // gemaakt door adam in samenwerking met Mark
	map = get_empty_map(20);
	string line; 
	ifstream myfile ("map.txt"); 
	int index = 0;
	if (myfile.is_open()){ 
		while ( getline (myfile, line) ){
			stringstream ss; 
			ss << line; 
			string temp; 
			int found;
			if (line.find("room") != string::npos) {
				while (!ss.eof()) { 
					ss >> temp;
					if (stringstream(temp) >> found && found != index+1){
						map[index].push_back(found);
					}
					temp = "";
				}
				index++;
			}
			else if (line.find("wumpus") != string::npos) {
				while (!ss.eof()) { 
					ss >> temp;
					if (stringstream(temp) >> found){
						wumpus = found;
						break;
					}
				}
			}
			else if (line.find("pits") != string::npos) {
				while (!ss.eof()) { 
					ss >> temp;
					if (stringstream(temp) >> found){
						pits.push_back(found);
					}
					temp = "";
				}
			}
			else if (line.find("bats") != string::npos) {
				while (!ss.eof()) { 
					ss >> temp;
					if (stringstream(temp) >> found){
						bats.push_back(found);
					}
					temp = "";
				}
			}
		}
		myfile.close();
	}
	else{ 
		animatetext("Unable to open file");
	} 
}


vector<vector<int>> make_map(int room_amount){ // Gemaakt door Adam
	// Vult de lege map met voor elke kamer 3 connecties. de output is een nested vector (int).
	// De plaat in de nested vector geeft aan over welke kamer het gaat. Dus de 0ste vector is kamer 1. 
	vector<vector<int>> map = get_empty_map(room_amount);
	int redo;
	
	for(size_t i = 0; i < map.size(); i++){
		for(unsigned int j = 0; j < 3; j++){
			if(map[i].size() > 2){
				break;
			}
			while (true){
				redo++;
				int x = (rand() % room_amount);
				if(i != x && map[x].size() < 3){
					if(map[i].size() == 0 || (map[i].size() == 1 && map[i][0] != x) || (map[i].size() == 2 && map[i][0] != x && map[i][1] != x)){
						redo = 0;
						map[x].push_back(i);
						map[i].push_back(x);
						break;
					}
				}
				if (redo == 10){  // Sometimes it fails near the end. If that happens it has to restart.
					redo = 0;
					map = get_empty_map(room_amount);
					i = 0;
					j = 0;
					break;
				}
			}
		}
	}
	for(unsigned int i = 0; i < map.size();i++){
		for(unsigned int k = 0; k < map[i].size(); k++){
		map[i][k]++;
		}
	}
	return map;
}


bool Gamemode(){ // Deze functie vraagt de gebruiker in welke mode hij/zij wil spelen en zorgt ervoor dat de bijbehorende map word geladen // origineel gemaakt door Jeff, bijgewerkt door Adam
	int gamemode;
	animatetext("Enter 1 to play a random map, or enter 2 to play the map from the config file.\n");
	cin >> gamemode;
	if(gamemode == 1){
		return true;
	}
	return false;
}


void printRoundInfo(vector<vector<int>> map, int wumpus, vector<int> bats, vector<int> pits){ // Gemaakt door Mark
    string answer;
    animatetext("Would you like to see the info for this round? (Y/N).\n");
    cin >> answer;
    if(answer == "Y" || answer == "y"){
        replay(map);
	animatetext("\nThe wumpus started in room: " + to_string(wumpus));
	animatetext("\nThe bats were in the rooms: ");
	for(unsigned int i=0; i<bats.size(); i++){
		cout<<bats[i] << ", ";
	}
	cout << "\nThe pits were in the rooms: ";
	for(unsigned int j=0; j<pits.size(); j++){
		cout<<pits[j] << ", ";
	}
	cout << "\n";
    }
}


int main(){ // deze code bevat onderdelen van iedereen omdat dit de "Hoofdfunctie is"
	system("color 0a");
	bool aiwin = false;
	srand(time(NULL));
	int wumpusgevonden = -1; // zolang hij hem niet heeft gevonden, blijft dit -1 als hij de wumpus heeft gevonden word deze hier bewaard zodat de jacht kan beginnen
	vector<int>rooms_to_avoid = {};
	bool normalmode;
	bool robomode = true;
	string showstat = "";
	game_Info("ASCII_Logo_Art.txt", "Game_Info.txt"); //print het startscherm en vraagt of je instructies wil
	string Nogmaalsspelen = ""; //begint de loop waarin je meerdere rondes van het spel kan spelen

	while(!(Nogmaalsspelen=="N") && !(Nogmaalsspelen == "n")){ // hier word het spel gestart
		vector<int>inefficient_rooms = {1};
		int wumpus;
		int arrowcount =5;
		vector<int>Bats;
		vector<int>Pits;
		vector<vector<int>> Map;
		int Playerlocation = 1; //hier word de speler in het spel geplaatst deze is altijd hetzelfde
		if(robomode){
			normalmode = Gamemode();
		}
		else{
			normalmode = false;
		}
		if(normalmode){
			Map = make_map(20); //maakt random map
			get_entities(wumpus, Bats, Pits ); //verandert the variables die worden meegegeven
			make_map_file(Map,wumpus,Bats,Pits);
		}
		else{
			read_config_file(Map, wumpus, Bats, Pits);
		}
		if(robomode){
			animatetext("Press 1 to play the game yourself, or press 0 to make an AI solve that level.\n");
			cin >> robomode;
		}
		else{
			robomode = 0;
		}
		while(robomode != 1 && robomode !=0){
			animatetext("Invalid anwser, Please enter 1 to play yourself, or press 2 to make the computer play that level.\n");
			cin >> robomode;
		}
		if(robomode == 1){
			player_action(Playerlocation,Map,wumpus,Bats,Pits,arrowcount, normalmode); //Hier word het spel gespeeld, met de map die word bepaald uit de gamemode functie
		}
		else{
			robot_action(Playerlocation,Map,wumpus,Bats,Pits,arrowcount,normalmode,rooms_to_avoid,wumpusgevonden,aiwin,inefficient_rooms);
		}
		printRoundInfo(Map, wumpus, Bats, Pits);
		animatetext("Would you like to see the statistics (Y/N).\n");
		cin >> showstat;
		if(showstat == "Y" || showstat == "y"){
			read_stats_file();
		}
		animatetext("Would you like to try again Y/N?.\n"); // vraagt of je nogmaals wil spelen
		if(robomode == 0){
			if(aiwin == 1){
				cin >> Nogmaalsspelen;
				robomode = 1;
				rooms_to_avoid = {};
				wumpusgevonden = -1;
				aiwin = 0;
			}
			else{
				Nogmaalsspelen = "Y";
				cout << "Y" << endl << "I will play till I win!" << endl;
			}
		}
		else{
		cin >> Nogmaalsspelen;
		}
	}
}