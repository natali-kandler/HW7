#include <stdio.h>
#include <stdbool.h>
#include "linked-list.h"
#include "grades.h"

int main() {
  char *name1 = "Natali";
  char *name2 = "Ziv";
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
  int id2 = 22;
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
  grades_print_student(grade_list, id1);
  grades_add_student(grade_list, name2, id2);
  grades_add_grade(grade_list, course_name1, id2, grade1);
  grades_add_grade(grade_list, course_name2, id2, grade2);
  grades_print_student(grade_list, id2);
  grades_print_all(grade_list);
  return 0;
}