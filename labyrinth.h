#ifndef LABYRINTH_H
#define LABYRINTH_H

class Labyrinth final
{
public:
  Labyrinth(int m, int n);
  ~Labyrinth();
  void show() const;

private:
  void generate();

private:
  int m_m;
  int m_n;
  int** m_data;
};

#endif // LABYRINTH_H
