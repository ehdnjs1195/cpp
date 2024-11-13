#include <string.h>
#include <iostream>

class Photon_Cannon {
  /*
   나머지 인스턴스들은 모두 단순히 값이기 때문에 복사 생성자에서 값을 복사하게 되는 것임. (메모리 주소가 아님!)
   기본 자료형(int, float, char 등)의 경우, 복사가 이루어질 때 값 자체가 새로운 메모리 주소에 복사됩니다.
   예를 들어, hp나 shield 같은 int 변수를 복사하면, pc1과 pc2는 각각 독립된 메모리 주소에 동일한 값을 가집니다.
  */
  int hp, shield;
  int coord_x, coord_y;
  int damage;

  char *name; // 얘는 포인터로 정의했기 때문에 주소값을 갖게 되는 것임.
  /*
    반면에 char* name처럼 포인터 변수는 주소 값을 저장합니다
    얕은 복사를 할 경우, 복사된 포인터는 원본 포인터가 가리키고 있는 같은 메모리 주소를 가리키게 됩니다.
    즉, 두 객체가 동일한 힙 메모리를 가리키기 때문에 한쪽에서 메모리를 해제하면 다른 쪽이 가리키는 메모리가 유효하지 않게 되어 메모리 오류가 발생할 수 있습니다.
    이를 방지하기 위해 name에 대해서는 깊은 복사를 해주어야 하며, 새로 할당한 메모리에 문자열 내용을 복사합니다.
   */
 public:
  Photon_Cannon(int x, int y);
  Photon_Cannon(int x, int y, const char *cannon_name);
  Photon_Cannon(const Photon_Cannon &pc);
  ~Photon_Cannon();

  void show_status();
};
Photon_Cannon::Photon_Cannon(int x, int y) {
  hp = shield = 100;
  coord_x = x;
  coord_y = y;
  damage = 20;

  name = NULL;
}
Photon_Cannon::Photon_Cannon(const Photon_Cannon &pc) {
  std::cout << "복사 생성자 호출! " << std::endl;
  hp = pc.hp;
  shield = pc.shield;
  coord_x = pc.coord_x;
  coord_y = pc.coord_y;
  damage = pc.damage;

  name = new char[strlen(pc.name) + 1]; // 복사 생성자에서 깊은 복사를 하도록 써주는 이유가 name이란 인스턴스 변수가 포인터로 정의되어 있었기 때문이다.
  strcpy(name, pc.name);
}
Photon_Cannon::Photon_Cannon(int x, int y, const char *cannon_name) {
  hp = shield = 100;
  coord_x = x;
  coord_y = y;
  damage = 20;

  name = new char[strlen(cannon_name) + 1];
  strcpy(name, cannon_name);
}
Photon_Cannon::~Photon_Cannon() {
  if (name) delete[] name;
}
void Photon_Cannon::show_status() {
  std::cout << "Photon Cannon :: " << name << std::endl;
  std::cout << " Location : ( " << coord_x << " , " << coord_y << " ) "
            << std::endl;
  std::cout << " HP : " << hp << std::endl;
}
int main() {
  Photon_Cannon pc1(3, 3, "Cannon");
  Photon_Cannon pc2 = pc1;

  pc1.show_status();
  pc2.show_status();
}