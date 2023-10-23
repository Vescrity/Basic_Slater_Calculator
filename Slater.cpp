#include <stdio.h>
#include <string>
#include <math.h>
using namespace std;
char ll[] = "spdfghijk";
class grp_lable
{
  int n, l;

public:
  string get_name()
  {
    return to_string(n) + ll[l];
  }
  grp_lable operator++(int)
  {
    grp_lable tmp(*this);
    l++;
    if (l == n)
    {
      l = 0;
      n++;
    }
    return tmp;
  }
  void init()
  {
    n = 1;
    l = 0;
  }
  int get_n() { return n; }
  bool is_sp() { return l < 2; }
  bool is_1s() { return n == 1; }
};
class grp
{
public:
  int num;
  grp_lable lable;
} grp_list[999];
int cnt, Z;
int main()
{
  grp_lable l;
  l.init();
  int t;
  printf("Enter Z:");
  scanf("%d", &Z);

  do
  {
    printf("Enter the e_number of %s, -1 to end:", l.get_name().c_str());
    scanf("%d", &t);
    if (t != -1)
    {
      grp_list[cnt].num = t;
      grp_list[cnt++].lable = l++;
    }
  } while (t != -1);
  long double sum = 0;
  for (int i = 0; i < cnt; i++)
  {
    grp &crt = grp_list[i];
    grp &nxt = grp_list[i + 1];
    if (crt.lable.is_1s())
    {
      sum += crt.num * pow(Z - (crt.num - 1) * 0.3, 2);
    }
    else
    {
      int s_n = crt.num;
      long double sig = 0;
      if (crt.lable.is_sp())
      {
        s_n += nxt.num;
      }
      sig += 0.35 * (s_n - 1);
      for (int j = 0; j < i; j++)
      {
        grp &crj = grp_list[j];
        if (crt.lable.is_sp())
        {
          int dn = crt.lable.get_n() - crj.lable.get_n();
          if (dn >= 2)
            sig += crj.num;
          else
            sig += 0.85 * crj.num;
        }
        else
        {
          sig += crj.num;
        }
      }
      sum += s_n * pow((Z - sig) / (1.0 * crt.lable.get_n()), 2);
      i += crt.lable.is_sp();
    }
  }
  printf("Answer=%20.10llf\n", sum * (-13.6));
}
