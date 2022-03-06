#include <windows.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
using namespace std;

string name[2111];             // 从 0 开始
bool name_visited[2111];       // 从 0 开始
int remained, n, name_[2111];  // 从 1 开始
string update_log = R"(更新日志 V2.0 2022/1/31

新版特性：
1. 名单将会自动重载，无需重新运行程序；
2. 增加查看更新日志功能；
3. 现在可以自由选择是否排除之前的人；
4. 开始支持自定义名单。
)";

void no_exclude_repeated();
void exclude_repeated();
void show_update_log();
void start_error();
void start();
void show_update_log_error();
void init();

template <typename T>
inline T read() {
  T X = 0;
  bool flag = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') flag = 0;
    if (ch == 'U') {
      show_update_log();
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    X = (X << 1) + (X << 3) + ch - '0';
    ch = getchar();
  }
  if (flag) return X;
  return ~(X - 1);
}

void no_exclude_repeated() {
  cout << "请输入要抽取的人的个数：";
  int num;
  cin >> num;
  while (true) {
    for (register int i = 1; i <= num; ++i) {
      do {
        name_[i] = rand() % n;
      } while (name_visited[name_[i]]);
      name_visited[name_[i]] = true;
    }
    system("cls");
    cout << "抽取结果：" << endl;
    for (register int i = 1; i <= num; ++i) {
      cout << name[name_[i]] << ' ';
    }
    cout << endl << endl;
    cout << "按下回车键进行下一轮抽取。";
    for (register int i = 0; i < n; ++i) {
      name_visited[i] = false;
    }
    getchar();
  }
}

void exclude_repeated() {
  cout << "请输入要抽取的人的个数：";
  int num;
  cin >> num;
  while (true) {
    for (register int i = 1; i <= num; ++i) {
      do {
        name_[i] = rand() % n;
      } while (name_visited[name_[i]]);
      name_visited[name_[i]] = true;
    }
    system("cls");
    cout << "抽取结果：" << endl;
    for (register int i = 1; i <= num; ++i) {
      cout << name[name_[i]] << ' ';
    }
    cout << endl << endl;
    cout << "按下回车键进行下一轮抽取。";
    remained -= num;
    if (remained < num) {
      cout << endl;
      cout << "（列表已经不足下一轮抽取了，下一轮起，之前抽取到过的将会重新被抽"
              "取。）";
      for (register int i = 0; i < n; ++i) {
        name_visited[i] = false;
      }
      remained = n;
    }
    getchar();
  }
}

void show_update_log_error() {
  cout << "输入错误，请重新输入。" << endl;
  show_update_log();
  return;
}

void show_update_log() {
  cout << update_log << endl;
  cout << endl;
  cout << "输入：1. 返回上级；2. 访问历史更新日志。";
  cout << endl;
  cout << endl << ">";
  int op;
  cin >> op;
  switch (op) {
    case 1:
      system("cls");
      start();
    case 2:
      system("explorer https://www.cnblogs.com/g-mph/p/15858606.html");
      cout << endl;
      start();
    default:
      system("cls");
      show_update_log_error();
  }
  return;
}

void start_error() {
  cout << "输入错误，请重新输入。" << endl;
  start();
  return;
}

void start() {
  cout << "输入 'U' 以查看更新日志；\n输入 'Y' 以排除抽取过的人；\n输入 'N' "
          "以不排除抽取过的人。";
  cout << endl;
  cout << endl << ">";
  char ch;
  cin >> ch;
  system("cls");
  switch (ch) {
    case 'U':
      show_update_log();
    case 'u':
      show_update_log();
    case 'Y':
      exclude_repeated();
    case 'y':
      exclude_repeated();
    case 'N':
      no_exclude_repeated();
    case 'n':
      no_exclude_repeated();
    default:
      start_error();
  }
  return;
}

void init() {
  cout << "请将名单放入同文件夹 name 文件中，放入后请重启此程序。" << endl;
  srand(time(NULL));
  freopen("name", "r", stdin);
  cin >> n;
  remained = n;
  for (register int i = 0; i < n; ++i) {
    cin >> name[i];
  }
  fclose(stdin);
  freopen("CON", "r", stdin);
  return;
}

int main() {
  init();
  start();
  return 0;
}