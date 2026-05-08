#include <ctype.h>
#include <dirent.h>
#include <fstream>
#include <iostream>

using namespace std;

void listProcesses() {
  DIR *dir = opendir("/proc");
  if (dir == NULL) {
    perror("Could not open /proc");
    return;
  }

  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    if (isdigit(entry->d_name[0])) {
      string pid = entry->d_name;
      string commPath = "/proc/" + pid + "/comm";

      ifstream commFile(commPath);
      string procName;

      if (getline(commFile, procName)) {
        cout << "PID: " << pid << " \t Name: " << procName << endl;
      }
    }
  }
  closedir(dir);
}

int main() {
  listProcesses();
  return 0;
}
