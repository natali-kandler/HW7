#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "linked-list.h"
#include "grades.h"

int main() {
  char *name1 = "Natali";
  char *name2 = "Ziv";
  char *name3 = "Noa";
  char *course_name1 = "mamat";
  char *course_name2 = "mavlas";
  char *course_name3 = "infi";
  char *course_name4 = "algrbra";
  char *course_name5 = "mamat";
  int grade1 = 99;
  int grade2 = 95;
  int grade3 = 96;
  int grade4 = 97;
  int grade5 = 98;
  int id1 = 11;
  int id2 = 11;
  int id3 = 33;
  int id4 = 11;
  float avg1;
  float avg3;
  //float avg2;
  char *out = NULL;
  struct grades *grade_list = grades_init();
  grades_add_student(grade_list, name1, id1);
  grades_add_grade(grade_list, course_name1, id1, grade1);
  grades_add_grade(grade_list, course_name2, id1, grade2);
  grades_add_grade(grade_list, course_name3, id1, grade3);
  grades_add_grade(grade_list, course_name4, id1, grade4);
  grades_add_grade(grade_list, course_name5, id1, grade5);
  grades_add_grade(grade_list, course_name5, id1, grade5);
  grades_add_grade(grade_list, course_name1, id2, grade1);
  grades_add_grade(grade_list, course_name2, id2, grade2);
  grades_add_student(grade_list, name3, id3);
  avg1 = grades_calc_avg(grade_list, id1, &out);
  printf("avg of id1: %f\n", avg1);
  avg3 = grades_calc_avg(grade_list, id3, &out);
  printf("avg of id3: %f\n", avg3);///no free!!!!
  grades_print_student(grade_list, id1);
  grades_add_student(grade_list, name2, id2);
  grades_add_grade(grade_list, course_name1, id2, grade1);
  grades_add_grade(grade_list, course_name2, id2, grade2);
  grades_print_student(grade_list, id2);
  grades_print_all(grade_list);
  grades_destroy(grade_list);
  return 0;
}