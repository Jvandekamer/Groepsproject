#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

void replay(vector<vector<int>> map){
	// Dit is alleen om de map uit te printen 
	for(unsigned int i=0; i<map.size(); i++){
		cout << "Room " << i+1 << " is connected with: ";
		for(unsigned int j=0; j<map[i].size(); j++){
			cout << map[i][j] << ", ";
		}
		cout << "\n";
	}
	cout << "\n";
}


void game_Info(string logo_txt, string info_txt){
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
        cout << "Unable to open logo file \n";
    }
    
    string user_input;
    cout << "WOULD YOU LIKE TO SEE THE INSTRUCTIONS? (Y/N) ";
    cin >> user_input;
    while(user_input != "Y" && user_input != "y" && user_input != "N" && user_input != "n"){
        cout << "WOULD YOU LIKE TO SEE THE INSTRUCTIONS? (Y/N) ";
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
                cout << info_lines[i] << endl;
            }
        }
        else{
        cout << "Unable to open info text file.";
        }
    }
}


int Checklocation(int Playerlocation,vector<vector<int>>Map,int wumpus){
	if(Playerlocation==wumpus){
		return 1;
	}
// als er nieuwe elementen in het spel zet deze hier dan in met een else if statement
	else{ // dit betekend dat de kamer leeg is
		return 0;
	}
}


string checksurrounding(int Playerlocation, vector<vector<int>>Map,int wumpus){
	string Warning = "";
	bool wumpdetected; // variable die laat zien of de wumpus is gespot
	for(int i=0; i < Map[Playerlocation-1].size(); i++){ // hier check je voor de hazzards op 1 kamer afstand
		if(Map[Playerlocation-1][i]==wumpus){
			wumpdetected = true;
		}
		// hier kan je de nieuwe hazzards toevoegen voor detectie
	}
	for(int j=0; j < Map[Playerlocation-1].size();j++){ // hier check je voor de hazzards op 2 kamers afstand
		int kamer = Map[Playerlocation-1][j];
		for(int k = 0; k < Map[kamer-1].size();k++){
			if(Map[kamer-1][k] == wumpus){
				wumpdetected = true;
			}
			// hier kan je de neiuwe hazzards toevoegen voor detecie
		}
	}
	if(wumpdetected == 1){
		Warning+="U smell something nearby.\n";
	}
	return Warning;
}


void Beweeg_speler(int & Playerlocation,vector<vector<int>> Map){
	int wumpus = 8; // dit is de kamer waar de wumpus zich bevind.
	while(true){
		// Hier geven we de speler wat extra informatie over wat er zich in de kamers om hem heen bevint
		string Warning = checksurrounding(Playerlocation,Map,wumpus);
		if(Warning.size() > 0){
			cout << Warning;
			cout << endl;
		}
		cout << "U are currently in room: " << Playerlocation << endl;
		cout << "Connected rooms are: ";
		for(int i =0; i < Map[Playerlocation-1].size(); i++){
			cout << Map[Playerlocation-1][i] << " ";
		}
		cout << endl;
		cout << "What room would u like to go to? " << endl;
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
			cout << "That room cannot be reached from my current position" << endl; // als de ingegeven kamer niet overeen kwam met een van de mogelijkheden dan print hij deze melding
			cout << "What room would u like to go to? " << endl; //en vraagt hij op nieuw om een locatie
			cin >> Playerlocation;
		}
		cout << endl;
		//vanaf hier gaan we checken wat er in de huidge kamer zit, en wat daarvan het gevolg is
		int inhoud_huidige_kamer = Checklocation(Playerlocation,Map,wumpus); //geeft nul als de kamer leeg is, geeft 1 als er een wumpus in de kamer zit. Als er nieuwe elenten in het spel komen voeg die hier aan toe met een nieuwe int
		if(inhoud_huidige_kamer==1){
			cout << "U Where killed by the wumpus" << endl;
			break; // deze breekt de loop en stopt dus het spel
		}
		else{ // als de waarde niet een van de bovenstaande is dan mag de speler verder met spelen
			continue; 
		}
	}
}


void make_map_file (vector<vector<int>> map) {
    ofstream myfile; 
    myfile.open("map.txt");
    for(unsigned int i=0; i<map.size(); i++){
        myfile << i+1 << "; ";
        for(unsigned int j=0; j<map[i].size(); j++){
            myfile << map[i][j] << ", ";
        }
        myfile << "\n";
    }
    myfile << "\n";
    myfile.close(); 
}


vector<vector<int>> get_empty_map(int room_amount){
	// een een lege map een te maken, room_amount geeft aan hoeveel kamers de map bevat
	vector<vector<int>> Empty_map = {};
	for(int i=0; i<room_amount; i++){
		Empty_map.push_back({});
	}
	return Empty_map;
}


vector<vector<int>> read_map_file () { 
    vector<vector<int>> map = get_empty_map(20);
    string line; 
    ifstream myfile ("map.txt"); 
    int index = 0;
    if (myfile.is_open()){ 
        while ( getline (myfile, line) ){
            stringstream ss; 
            ss << line; 
            string temp; 
            int found; 
            while (!ss.eof()) { 
                ss >> temp;
                if (stringstream(temp) >> found && found != index+1){
                    map[index].push_back(found);
                }
                temp = "";
            }
            index++;
        }
        myfile.close(); 
    }
    else{ 
        cout << "Unable to open file";
    } 
    return map;
}


vector<vector<int>> make_map(int room_amount){
	// Vult de lege map met voor elke kamer 3 connecties. de output is een nested vector (int).
	// De plaat in de nested vector geeft aan over welke kamer het gaat. Dus de 0ste vector is kamer 1. 
	srand((unsigned) time(0));
	vector<vector<int>> map = get_empty_map(room_amount);
	int redo;
	
	for(int i = 0; i < map.size(); i++){
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
					redo == 0;
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
	replay(map);
	return map;
}


vector<vector<int>> Dev_map(){ //Dit is de functie die er voor zorgt dat de gebruiker zijn eigen map kan spelen later worden hier nog extra dingen aan toegevoegd zoals de wumpus locatie en andere onderdelen die je tegen kunt komen in het spel
	vector<vector<int>> Map = {{2,4,8},{1,3,7},{2,4,6},{1,3,5},{4,6,8},{3,5,7},{2,6,8},{1,5,7}}; // dit is de map, Het kamer nummer is de index van de vector -1 dus de eerste vector in de vector is kamer 1
	return Map;
}


vector<vector<int>>Gamemode(){ // Deze functie vraagt de gebruiker in welke mode hij/zij wil spelen en zorgt ervoor dat de bijbehorende map word geladen
	int gamemode;
	cout << "Enter 1 for normal mode, or enter 2 for developer mode" << endl;
	cin >> gamemode;
	if(gamemode == 1){
		return make_map(20); // hier roept hij de random map aan
	}
	return read_map_file(); // hier roept hij de developer map aan
}


void printRoundInfo(vector<vector<int>> Map, string configuratie_txt){
    string answer;
    cout << "Would you like to see this round info? (Y/N) " << endl;
    cin >> answer;
    if(answer == "Y" || answer == "y"){
        replay(Map);
        vector<vector<string>> map_info;
        string setting_line;
        ifstream configuratie (configuratie_txt);
        if (configuratie.is_open()){
            int start_index;
            int room_number;
            while (getline(configuratie, setting_line)){
                if (setting_line.find("wumpus") != string::npos){
                    start_index = setting_line.find("wumpus");
                    cout << "De Wumpus zit in kamer: " << setting_line[start_index+7] << endl;
                }
            }
        }

    }
}


int main(){
	game_Info("ASCII_Logo_Art.txt", "Game_Info.txt"); //print het startscherm en vraagt of je instructies wil
	bool Nogmaalsspelen = true; //begint de loop waarin je meerdere rondes van het spel kan spelen
	while(Nogmaalsspelen==true){ // hier word het spel gestart
		int Playerlocation = 1; //hier word de speler in het spel geplaatst deze is altijd hetzelfde
		vector<vector<int>> Map = Gamemode(); //Hier word bepaald voor welke map er word gekozen
		make_map_file(Map);
		Beweeg_speler(Playerlocation,Map); //Hier word het spel gespeeld, met de map die word bepaald uit de gamemode functie
//		printRoundInfo(Map,configbestand); (moet nog worden afgemaakt
		cout << "Would u like to try again?" << endl; // vraagt of je nogmaals wil spelen
		cin >> Nogmaalsspelen; // 1 betekend nog een ronde spelen, 0 zorgt ervoor dat je het spel afsluit
	}
}
