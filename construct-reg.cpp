#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int insert_path(string::iterator& it, const string::iterator& end, const char delim, string& data, const string& value) {

	for (; it != end; ++it) {
		if (*it == delim) {

			*it = value[value.size() - 1];

			for(int i = value.size() - 2; i >= 0; --i) {
				it = data.insert(it, value[i]);
			}
			
			return 0;
		}
	}

	return -1;
}

int construct_reg(const string& reg_path, const string& bat_path, const string& ico_path) {

	fstream reg(reg_path);
	
	if (!reg.is_open())
		return -1;

	string reg_content(istreambuf_iterator<char>(reg), (istreambuf_iterator<char>()));

	string::iterator it = reg_content.begin();
	insert_path(it, reg_content.end(), '$', reg_content, ico_path);
	insert_path(it, reg_content.end(), '$', reg_content, bat_path);
	insert_path(it, reg_content.end(), '$', reg_content, ico_path);
	insert_path(it, reg_content.end(), '$', reg_content, bat_path);

	reg.seekp(0);
	reg << reg_content;

	return 0;
}

void escape_backslashes(string& str) {

	for (int i = 0; i < str.size(); ++i) {
		if (str[i] == '\\') {
			str.insert(i, 1, '\\');
			++i;
		}
	}
}

int main(int argc, char *argv[]) {

	string exec_path(argv[1]);

	if (argc < 2)
		return -1;

	string::size_type delim = exec_path.find_last_of('\\');

	exec_path.replace(delim, exec_path.size() - 1, "\\open-emacs\\emacs.bat");
	string bat_path(exec_path);

	exec_path.replace(delim, exec_path.size() - 1, "\\open-emacs\\add-to-context-menu.reg");
	string reg_path(exec_path);

	exec_path.replace(delim, exec_path.size() - 1, "\\open-emacs\\emacs.ico");
	string ico_path(exec_path);

	escape_backslashes(bat_path);
	escape_backslashes(ico_path);

	return construct_reg(reg_path, bat_path, ico_path);
}