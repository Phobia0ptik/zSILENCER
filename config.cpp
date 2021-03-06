#include "config.h"
#include "team.h"
#include <sstream>

Config::Config(){
	if(!Load()){
		LoadDefaults();
		Save();
	}
}

Config & Config::GetInstance(void){
	static Config instance;
	return instance;
}

void Config::Save(void){
	SDL_RWops * file = SDL_RWFromFile("config.cfg", "w");
	if(file){
		char temp[256];
		WriteString(file, "fullscreen", fullscreen ? "1" : "0");
		WriteString(file, "teamcolors", teamcolors ? "1" : "0");
		sprintf(temp, "%d", defaultagency); WriteString(file, "defaultagency", temp);
		WriteString(file, "defaultgamename", defaultgamename);
		sprintf(temp, "%d", defaulttechchoices[0]); WriteString(file, "defaulttechchoices0", temp);
		sprintf(temp, "%d", defaulttechchoices[1]); WriteString(file, "defaulttechchoices1", temp);
		sprintf(temp, "%d", defaulttechchoices[2]); WriteString(file, "defaulttechchoices2", temp);
		sprintf(temp, "%d", defaulttechchoices[3]); WriteString(file, "defaulttechchoices3", temp);
		sprintf(temp, "%d", defaulttechchoices[4]); WriteString(file, "defaulttechchoices4", temp);
		WriteKey(file, "keymoveup", keymoveupbinding, keymoveupoperator);
		WriteKey(file, "keymovedown", keymovedownbinding, keymovedownoperator);
		WriteKey(file, "keymoveleft", keymoveleftbinding, keymoveleftoperator);
		WriteKey(file, "keymoveright", keymoverightbinding, keymoverightoperator);
		WriteKey(file, "keylookupleft", keylookupleftbinding, keylookupleftoperator);
		WriteKey(file, "keylookupright", keylookuprightbinding, keylookuprightoperator);
		WriteKey(file, "keylookdownleft", keylookdownleftbinding, keylookdownleftoperator);
		WriteKey(file, "keylookdownright", keylookdownrightbinding, keylookdownrightoperator);
		WriteKey(file, "keynextinv", keynextinvbinding, keynextinvoperator);
		WriteKey(file, "keynextcam", keynextcambinding, keynextcamoperator);
		WriteKey(file, "keyprevcam", keyprevcambinding, keyprevcamoperator);
		WriteKey(file, "keydetonate", keydetonatebinding, keydetonateoperator);
		WriteKey(file, "keyjump", keyjumpbinding, keyjumpoperator);
		WriteKey(file, "keyjetpack", keyjetpackbinding, keyjetpackoperator);
		WriteKey(file, "keyactivate", keyactivatebinding, keyactivateoperator);
		WriteKey(file, "keyuse", keyusebinding, keyuseoperator);
		WriteKey(file, "keyfire", keyfirebinding, keyfireoperator);
		WriteKey(file, "keychat", keychatbinding, keychatoperator);
		WriteKey(file, "keydisguise", keydisguisebinding, keydisguiseoperator);
		WriteKey(file, "keynextweapon", keynextweaponbinding, keynextweaponoperator);
		SDL_RWclose(file);
	}
}

bool Config::Load(void){
	SDL_RWops * file = SDL_RWFromFile("config.cfg", "r");
	if(file){
		char line[256];
		while(RWgets(file, line, sizeof(line))){
			char * variable = strtok(line, "=");
			char * data = strtok(NULL, "=");
			if(variable && data){
				if(CompareString(variable, "fullscreen")){ if(atoi(data) == 0){ fullscreen = false; }else{ fullscreen = true; } }
				if(CompareString(variable, "teamcolors")){ if(atoi(data) == 0){ teamcolors = false; }else{ teamcolors = true; } }
				if(CompareString(variable, "defaultagency")){ defaultagency = atoi(data); }
				if(CompareString(variable, "defaultgamename")){ ReadString(data, defaultgamename); }
				if(CompareString(variable, "defaulttechchoices0")){ defaulttechchoices[0] = atoi(data); }
				if(CompareString(variable, "defaulttechchoices1")){ defaulttechchoices[1] = atoi(data); }
				if(CompareString(variable, "defaulttechchoices2")){ defaulttechchoices[2] = atoi(data); }
				if(CompareString(variable, "defaulttechchoices3")){ defaulttechchoices[3] = atoi(data); }
				if(CompareString(variable, "defaulttechchoices4")){ defaulttechchoices[4] = atoi(data); }
				if(CompareString(variable, "keymoveup")){ ReadKey(data, &keymoveupbinding, &keymoveupoperator); }
				if(CompareString(variable, "keymovedown")){ ReadKey(data, &keymovedownbinding, &keymovedownoperator); }
				if(CompareString(variable, "keymoveleft")){ ReadKey(data, &keymoveleftbinding, &keymoveleftoperator); }
				if(CompareString(variable, "keymoveright")){ ReadKey(data, &keymoverightbinding, &keymoverightoperator); }
				if(CompareString(variable, "keylookupleft")){ ReadKey(data, &keylookupleftbinding, &keylookupleftoperator); }
				if(CompareString(variable, "keylookupright")){ ReadKey(data, &keylookuprightbinding, &keylookuprightoperator); }
				if(CompareString(variable, "keylookdownleft")){ ReadKey(data, &keylookdownleftbinding, &keylookdownleftoperator); }
				if(CompareString(variable, "keylookdownright")){ ReadKey(data, &keylookdownrightbinding, &keylookdownrightoperator); }
				if(CompareString(variable, "keynextinv")){ ReadKey(data, &keynextinvbinding, &keynextinvoperator); }
				if(CompareString(variable, "keynextcam")){ ReadKey(data, &keynextcambinding, &keynextcamoperator); }
				if(CompareString(variable, "keyprevcam")){ ReadKey(data, &keyprevcambinding, &keyprevcamoperator); }
				if(CompareString(variable, "keydetonate")){ ReadKey(data, &keydetonatebinding, &keydetonateoperator); }
				if(CompareString(variable, "keyjump")){ ReadKey(data, &keyjumpbinding, &keyjumpoperator); }
				if(CompareString(variable, "keyjetpack")){ ReadKey(data, &keyjetpackbinding, &keyjetpackoperator); }
				if(CompareString(variable, "keyactivate")){ ReadKey(data, &keyactivatebinding, &keyactivateoperator); }
				if(CompareString(variable, "keyuse")){ ReadKey(data, &keyusebinding, &keyuseoperator); }
				if(CompareString(variable, "keyfire")){ ReadKey(data, &keyfirebinding, &keyfireoperator); }
				if(CompareString(variable, "keychat")){ ReadKey(data, &keychatbinding, &keychatoperator); }
				if(CompareString(variable, "keydisguise")){ ReadKey(data, &keydisguisebinding, &keydisguiseoperator); }
				if(CompareString(variable, "keynextweapon")){ ReadKey(data, &keynextweaponbinding, &keynextweaponoperator); }
			}
		}
		SDL_RWclose(file);
		return true;
	}
	return false;
}

void Config::LoadDefaults(void){
	fullscreen = false;
	teamcolors = false;
	defaultagency = Team::NOXIS;
	strcpy(defaultgamename, "New Game");
	defaulttechchoices[0] = World::BUY_LASER | World::BUY_ROCKET;
	defaulttechchoices[1] = World::BUY_LASER | World::BUY_ROCKET;
	defaulttechchoices[2] = World::BUY_LASER | World::BUY_ROCKET;
	defaulttechchoices[3] = World::BUY_LASER | World::BUY_ROCKET;
	defaulttechchoices[4] = World::BUY_LASER | World::BUY_ROCKET;
	keymoveupbinding[0] = SDL_SCANCODE_UP; keymoveupbinding[1] = SDL_SCANCODE_UNKNOWN; keymoveupoperator = OR;
	keymovedownbinding[0] = SDL_SCANCODE_DOWN; keymovedownbinding[1] = SDL_SCANCODE_UNKNOWN; keymovedownoperator = OR;
	keymoveleftbinding[0] = SDL_SCANCODE_LEFT; keymoveleftbinding[1] = SDL_SCANCODE_UNKNOWN; keymoveleftoperator = OR;
	keymoverightbinding[0] = SDL_SCANCODE_RIGHT; keymoverightbinding[1] = SDL_SCANCODE_UNKNOWN; keymoverightoperator = OR;
	keyupbinding[0] = SDL_SCANCODE_UP; keyupbinding[1] = SDL_SCANCODE_UNKNOWN; keyupoperator = OR;
	keydownbinding[0] = SDL_SCANCODE_DOWN; keydownbinding[1] = SDL_SCANCODE_UNKNOWN; keydownoperator = OR;
	keyleftbinding[0] = SDL_SCANCODE_LEFT; keyleftbinding[1] = SDL_SCANCODE_UNKNOWN; keyleftoperator = OR;
	keyrightbinding[0] = SDL_SCANCODE_RIGHT; keyrightbinding[1] = SDL_SCANCODE_UNKNOWN; keyrightoperator = OR;
	keylookupleftbinding[0] = SDL_SCANCODE_UP; keylookupleftbinding[1] = SDL_SCANCODE_LEFT; keylookupleftoperator = AND;
	keylookuprightbinding[0] = SDL_SCANCODE_UP; keylookuprightbinding[1] = SDL_SCANCODE_RIGHT; keylookuprightoperator = AND;
	keylookdownleftbinding[0] = SDL_SCANCODE_DOWN; keylookdownleftbinding[1] = SDL_SCANCODE_LEFT; keylookdownleftoperator = AND;
	keylookdownrightbinding[0] = SDL_SCANCODE_DOWN; keylookdownrightbinding[1] = SDL_SCANCODE_RIGHT; keylookdownrightoperator = AND;
	keynextinvbinding[0] = SDL_SCANCODE_R; keynextinvbinding[1] = SDL_SCANCODE_UNKNOWN; keynextinvoperator = OR;
	keynextcambinding[0] = SDL_SCANCODE_S; keynextcambinding[1] = SDL_SCANCODE_UNKNOWN; keynextcamoperator = OR;
	keyprevcambinding[0] = SDL_SCANCODE_A; keyprevcambinding[1] = SDL_SCANCODE_UNKNOWN; keyprevcamoperator = OR;
	keydetonatebinding[0] = SDL_SCANCODE_D; keydetonatebinding[1] = SDL_SCANCODE_UNKNOWN; keydetonateoperator = OR;
	keyjumpbinding[0] = SDL_SCANCODE_TAB; keyjumpbinding[1] = SDL_SCANCODE_UNKNOWN; keyjumpoperator = OR;
	keyjetpackbinding[0] = SDL_SCANCODE_Q; keyjetpackbinding[1] = SDL_SCANCODE_UNKNOWN; keyjetpackoperator = OR;
	keyactivatebinding[0] = SDL_SCANCODE_SPACE; keyactivatebinding[1] = SDL_SCANCODE_UNKNOWN; keyactivateoperator = OR;
	keyusebinding[0] = SDL_SCANCODE_W; keyusebinding[1] = SDL_SCANCODE_UNKNOWN; keyuseoperator = OR;
	keyfirebinding[0] = SDL_SCANCODE_E; keyfirebinding[1] = SDL_SCANCODE_UNKNOWN; keyfireoperator = OR;
	keychatbinding[0] = SDL_SCANCODE_T; keychatbinding[1] = SDL_SCANCODE_UNKNOWN; keychatoperator = OR;
	keydisguisebinding[0] = SDL_SCANCODE_C; keydisguisebinding[1] = SDL_SCANCODE_UNKNOWN; keydisguiseoperator = OR;
	keynextweaponbinding[0] = SDL_SCANCODE_UNKNOWN; keynextweaponbinding[1] = SDL_SCANCODE_UNKNOWN; keynextweaponoperator = OR;
}

bool Config::KeyIsPressed(const Uint8 * keyboardstate, SDL_Scancode keybindings[2], bool keyoperator){
	if(keyoperator == OR || (keybindings[0] == SDL_SCANCODE_UNKNOWN || keybindings[1] == SDL_SCANCODE_UNKNOWN)){
		return keyboardstate[keybindings[0]] || keyboardstate[keybindings[1]] ? true : false;
	}else{
		return keyboardstate[keybindings[0]] && keyboardstate[keybindings[1]] ? true : false;
	}
}

bool Config::CompareString(const char * str1, const char * str2){
	int minsize = strlen(str1);
	if(strlen(str2) < minsize){
		minsize = strlen(str2);
	}
	if(strncmp(str1, str2, minsize) == 0){
		return true;
	}
	return false;
}

void Config::WriteKey(SDL_RWops * file, const char * variable, SDL_Scancode keybindings[2], bool keyoperator){
	char line[256];
	sprintf(line, "%s = %d %d %d\n", variable, keybindings[0], keyoperator, keybindings[1]);
	SDL_RWwrite(file, line, strlen(line), 1);
}

void Config::ReadKey(char * data, SDL_Scancode (*keybindings)[2], bool * keyoperator){
	std::istringstream stream(data);
	unsigned int key1 = 0;
	unsigned int keyop = false;
	unsigned int key2 = 0;
	while(stream.peek() == ' ' || stream.peek() == '\t'){ stream.ignore(); }
	stream >> key1;
	while(stream.peek() == ' ' || stream.peek() == '\t'){ stream.ignore(); }
	stream >> keyop;
	while(stream.peek() == ' ' || stream.peek() == '\t'){ stream.ignore(); }
	stream >> key2;
	(*keybindings)[0] = (SDL_Scancode)key1;
	if(keyop){
		*keyoperator = true;
	}else{
		*keyoperator = false;
	}
	(*keybindings)[1] = (SDL_Scancode)key2;
}

void Config::WriteString(SDL_RWops * file, const char * variable, const char * string){
	char line[256];
	sprintf(line, "%s = %s\n", variable, string);
	SDL_RWwrite(file, line, strlen(line), 1);
}

void Config::ReadString(const char * data, char * variable){
	for(int i = 0, j = 0; i < strlen(data); i++){
		if(j == 0 && (data[i] == ' ' || data[i] == '\t')){
			
		}else{
			variable[j++] = data[i];
		}
	}
}

char * Config::RWgets(SDL_RWops * file, char * buffer, int count){
	int i;
	buffer[count - 1] = '\0';
	for(i = 0; i < count - 1; i++){
		if(SDL_RWread(file, buffer + i, 1, 1) != 1){
			if(i == 0){
				return NULL;
			}
			break;
		}
		if(buffer[i] == '\n'){
			break;
		}
	}
	buffer[i] = '\0';
	return buffer;
}