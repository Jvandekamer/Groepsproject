#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <fstream>
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

void Beweeg_speler(int & Playerlocation,vector<vector<int>> Map){
	int wumpus = 1;
	while(true){
		cout << "U are currently in room: " << Playerlocation << endl;
		cout << "Connected rooms are: ";
		for(int i =0; i < Map[Playerlocation-1].size(); i++){
			cout << Map[Playerlocation-1][i] << " ";
		}
		cout << endl;
		cout << "What room would u like to go to? " << endl;
		int tmp = Playerlocation;
		cin >> Playerlocation;
		while(true){
			if(Playerlocation ==Map[tmp-1][0]){
				break;
			}
			if(Playerlocation ==Map[tmp-1][1]){
				break;
			}
			if(Playerlocation ==Map[tmp-1][2]){
				break;
			}
			cout << "That room cannot be reached from my current position" << endl;
			cout << "What room would u like to go to? " << endl;
			cin >> Playerlocation;
		}
		if(Playerlocation == wumpus){
			cout << "U where killed by the Wumpus, well played" << endl;
			break;
		}
		
	}
}

vector<vector<int>> get_empty_map(int room_amount){
	// een een lege map een te maken, room_amount geeft aan hoeveel kamers de map bevat
	vector<vector<int>> Empty_map = {};
	for(int i=0; i<room_amount; i++){
		Empty_map.push_back({});
	}
	return Empty_map;
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


vector<vector<int>> Dev_map(){ //Dit is de functie die er voor zorgt dat de gebruiker zijn eigen map kan spelen
	vector<vector<int>> Map = {{2,4,8},{1,3,7},{2,4,6},{1,3,5},{4,6,8},{3,5,7},{2,6,8},{1,5,7}}; // dit is de map, Het kamer nummer is de index van de vector -1 dus de eerste vector in de vector is kamer 1
 	srand(time(NULL));
	return Map;
}

vector<vector<int>>Gamemode(){
	int gamemode;
	cout << "Enter 1 for normal mode, or enter 2 for developer mode" << endl;
	cin >> gamemode;
	if(gamemode == 1){
		return make_map(8);
	}
	return Dev_map();
}
int main(){
	game_Info("ASCII_Logo_Art.txt", "Game_Info.txt");
	bool Nogmaalsspelen = true;
	while(Nogmaalsspelen==true){ // hier word het spel gestart
		int Playerlocation = 1; //hier word de speler in het spel geplaatst
		vector<vector<int>> Map = Gamemode();
		Beweeg_speler(Playerlocation,Map);
		cout << "Would u like to try again?" << endl;
		cin >> Nogmaalsspelen;
	}
}

