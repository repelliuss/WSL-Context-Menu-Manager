#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string construct_reg_deleter(string inputs[], int size) {

	string deleter_script;
	string capitalized_app_name = inputs[0];
	capitalized_app_name[0] = toupper(capitalized_app_name[0]);

	deleter_script += "@echo OFF\n";

	if (inputs[1] == "y") {
		deleter_script += "reg delete \"HKCR\\*\\shell\\Open with " + capitalized_app_name + "\"\n";
	}

	if (inputs[2] == "y") {
		deleter_script += "reg delete \"HKCR\\Directory\\Background\\shell\\Open " + capitalized_app_name + " Here\"\n";
	}

	deleter_script += "del scripts\\%app%.bat\n";
	deleter_script += "del deleter_script.bat\n";
	deleter_script += "pause";

	return deleter_script;
}

int create_file(string file_path, string data) {

	ofstream file(file_path);

	if (!file.is_open())
		return -1;

	file << data;

	file.close();

	return 0;
}

void parse_inputs(int argc, char* argv[], string inputs[], int& parsed_size) {

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

int main(int argc, char* argv[])
{

	if (argc < 4)
		return -1;

	int parsed_size;
	string inputs[4];

	parse_inputs(argc, argv, inputs, parsed_size);

	string deleter_path = ".\\deleter_script.bat";

	return create_file(deleter_path, construct_reg_deleter(inputs, parsed_size));
}
