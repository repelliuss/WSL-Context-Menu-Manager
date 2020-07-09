#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string escape_backslashes(string str) {

	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '\\') {
			str.insert(i, 1, '\\');
			++i;
		}
	}

	return str;
}

string construct_reg(string inputs[], int size) {

	string reg;
	string capitalized_app_name = inputs[2];
	capitalized_app_name[0] = toupper(capitalized_app_name[0]);

	reg += "Windows Registry Editor Version 5.00\n\n";

	if (inputs[8] == "y") {

		if(inputs[5] == "y") {
			reg += "[HKEY_CLASSES_ROOT\\*\\shell\\Open with " + capitalized_app_name + "]\n";
			reg += "@=\"Open &with &" + capitalized_app_name + "\"\n";
			reg += "\"Icon\"=\"" + escape_backslashes(inputs[0]) + "icons\\\\" + inputs[2] + ".ico\"\n\n";
		}

		if (inputs[6] == "y") {
			reg += "[HKEY_CLASSES_ROOT\\Directory\\Background\\shell\\Open " + capitalized_app_name + " Here]\n";
			reg += "@=\"Open &" + capitalized_app_name + " &Here\"\n";
			reg += "\"Icon\"=\"" + escape_backslashes(inputs[0]) + "icons\\\\" + inputs[2] + ".ico\"\n\n";
		}
	}

	if (inputs[5] == "y") {
		reg += "[HKEY_CLASSES_ROOT\\*\\shell\\Open with " + capitalized_app_name + "\\command]\n";
		reg += "@=\"\\\"" + escape_backslashes(inputs[0]) + "scripts\\\\" + inputs[2] + ".bat" + "\\\" \\\"%1%\\\" '%1' '%2'\"\n\n";
	}

	if (inputs[6] == "y") {
		reg += "[HKEY_CLASSES_ROOT\\Directory\\Background\\shell\\Open " + capitalized_app_name + " Here\\command]\n";
		reg += "@=\"\\\"" + escape_backslashes(inputs[0]) + "scripts\\\\" + inputs[2] + ".bat" + "\\\" '%V'\"\n\n";
	}

	return reg;
}

string construct_script(string inputs[], int size) {

	string script;

	script += "@echo OFF\nset launch_path=%1\n";
	script += "for /f \"delims=\" %%i in ('wsl wslpath -a %launch_path%') do set launch_path=%%i\n";
	script += "start ";
	if (inputs[4] != "cmd") {
		script += inputs[4] + " ";
	}
	script += "bash -c \"";
	if (inputs[3] == "y") {
		script += "export DISPLAY=$(cat /etc/resolv.conf | grep nameserver | awk '{print $2}'):" + inputs[7] + " && ";
	}

	script += "export PATH=$PATH:%WSLPATH% %WSLEXPORT% && ";
	script += inputs[1] + ' ' + "%launch_path%\"\n";

	return script;
}

int create_file(string file_path, string data) {

	ofstream file(file_path);

	if (!file.is_open())
		return -1;

	file << data;

	file.close();

	return 0;
}

void parse_inputs(int argc, char* argv[], string inputs[], int &parsed_size) {

	inputs[0] = argv[1];
	inputs[0].resize(inputs[0].size() - 1);

	parsed_size = 1;
	for (int i = 2; i < argc; ++i) {

		inputs[parsed_size] += argv[i];
		if (inputs[parsed_size][inputs[parsed_size].size() - 1] == ',') {
			inputs[parsed_size].resize(inputs[parsed_size].size() - 1);
			++parsed_size;
		}
		else inputs[parsed_size] += ' ';
	}
}


int main(int argc, char *argv[])
{

	if (argc < 10)
		return -1;

	int parsed_size;
	string inputs[10];

	parse_inputs(argc, argv, inputs, parsed_size);

	string reg_path = inputs[0] + "\\context-menu.reg";
	string script_path = inputs[0] + "\\scripts\\" + inputs[2] + ".bat";

	if (create_file(reg_path, construct_reg(inputs, parsed_size)) == 0) {
		if (create_file(script_path, construct_script(inputs, parsed_size)) == 0) {
			return 0;
		}
	}

	return -1;
}
