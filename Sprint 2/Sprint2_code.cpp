void printRoundInfo(vector<vector<int>> map, int wumpus, vector<int> bats, vector<int> pits){
    string answer;
    cout << "Would you like to see the info for this round? (Y/N) " << endl;
    cin >> answer;
    if(answer == "Y" || answer == "y"){
        replay(map);
	cout << "\nThe wumpus started in room: " << wumpus;
	cout << "\nThe bats were in the rooms: ";
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


///Dit is de eind code, hierbij was ik begonnen met de functionaliteit om een specifieke string binnen het tekst bestand op te zoeken. De rest is door Adam geimplementeerd.
void read_config_file (vector<vector<int>> & map, int & wumpus, vector<int> & bats, vector<int> & pits) { 
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
		cout << "Unable to open file";
	} 
}