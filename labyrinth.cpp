#include "labyrinth.h"

#include <iostream>
#include <random>

// https://habrahabr.ru/post/353104/

// more -> less walls
static const double THRESHOLD = 0.25;

Labyrinth::Labyrinth(int m, int n) :
  m_m(m),
  m_n(n),
  m_data(nullptr)
{
  // check
  if (m_m < 3) m_m = 3;
  if (m_n < 3) m_n = 3;

  // to odd
  if (m_m % 2 == 0) ++m_m;
  if (m_n % 2 == 0) ++m_n;

  generate();
}

Labyrinth::~Labyrinth()
{
  for (int i = 0; i < m_n; ++i)
  {
    delete[] m_data[i];
  }

  delete[] m_data;
}

void Labyrinth::generate()
{
  m_data = new int*[m_n];

  for (int i = 0; i < m_n; ++i)
  {
    m_data[i] = new int[m_m];
  }

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<double> dist(0.0, 1.0);

  for (int j = 0; j < m_n; ++j)
  {
    for (int i = 0; i < m_m; ++i)
    {
      if (i == 0 || i == m_m - 1 || j == 0 || j == m_n - 1)
      {
        m_data[j][i] = 1;
        continue;
      }

      if (i % 2 == 0 && j % 2 == 0)
      {
        if (dist(mt) > THRESHOLD)
        {
          m_data[j][i] = 1;

          // rand h or v cell
          int a = (dist(mt) > 0.5) ? 0 : ((dist(mt) > 0.5) ? 1 : -1);
          int b = (a != 0 ? 0 : (((dist(mt) > 0.5) ? 1 : -1)));

          m_data[j + a][i + b] = 1;
        }
      }
    }
  }
}

void Labyrinth::show() const
{
  std::cout << m_m << " " << m_n << std::endl;

  for (int j = 0; j < m_n; ++j)
  {
    for (int i = 0; i < m_m; ++i)
    {
      std::cout << (m_data[j][i] == 0 ? " " : "#");
    }

    std::cout << std::endl;
  }
}

