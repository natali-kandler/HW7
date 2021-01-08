// REMOVE extra libraries!!!!!!!!
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked-list.h"
#include "grades.h"

typedef struct list *plist_t;
typedef struct node *pnode_t;

int courses_clone(void *element, void **output);
void courses_destroy(void *element);
int student_clone(void *element, void **output);
void student_destroy(void *element);

struct student {
  int id;
  char *student_name;
  plist_t courses_list;
};

struct grades { //our list of students
  plist_t students;
};

struct courses {
  int grade;
  char *course_name;
};

int courses_clone(void *element, void **output) {
  if (element == NULL || output == NULL) {
    return 1;
  }
  struct courses *old_courses = (struct courses *) element;
  struct courses
      *new_courses = (struct courses *) malloc(sizeof(struct courses));
  new_courses->grade = old_courses->grade;
  new_courses->course_name =
      (char *) malloc(strlen(old_courses->course_name) + 1);
  if (new_courses->course_name == NULL) {
    free(new_courses);
    return 1;
  }
  strcpy(new_courses->course_name, old_courses->course_name);
  //for sure write it wrong !! check who you shulod return the clone value !!!!!!!
  *output = (void *) new_courses;
  return 0;
}

//free name_course and
void courses_destroy(void *element) {
  if (element == NULL) {
    return;
  }
  struct courses *courses = (struct courses *) element;
  free(courses->course_name);
  free(courses);
}

int student_clone(void *element, void **output) {
  if (element == NULL || output == NULL) {
    return 1;
  }
  struct student *old_student = (struct student *) element;
  struct student
      *new_student = (struct student *) malloc(sizeof(struct student));
  new_student->id = old_student->id;
  new_student->student_name =
      (char *) malloc(strlen(old_student->student_name) + 1);
  if (new_student->student_name == NULL) {
    free(new_student);
    return 1;
  }
  strcpy(new_student->student_name, old_student->student_name);
  new_student->courses_list = list_init(courses_clone, courses_destroy);
  pnode_t iterator = list_begin(old_student->courses_list);
  while (iterator != NULL) {
    pnode_t it_last_grade_new_student = list_end(new_student->courses_list);
    int x = list_insert(new_student->courses_list,
                        it_last_grade_new_student,
                        list_get(iterator));
    if (x != 0) {
      // check what to do if fail!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
    }
    iterator = list_next(iterator);
  }
  //for sure write it wrong !! check who you shulod return the clone value !!!!!!!
  *output = (void *) new_student;
  return 0;
}

void student_destroy(void *element) {
  if (element == NULL) {
    return;
  }
  struct student *student = (struct student *) element;
  free(student->student_name);
  list_destroy(student->courses_list);
  free(student);
}

struct grades *grades_init() {
  struct grades *new_grades = (struct grades *) malloc(sizeof(struct grades));
  if (new_grades == NULL) {
    return NULL;
  }
  new_grades->students = list_init(student_clone, student_destroy);
  return new_grades;
}

int grades_add_student(struct grades *grades, const char *name, int id) {
  struct student new_student;
  new_student.id = id;
  new_student.student_name = (char *) malloc(strlen(name) + 1); //not sure
  // why is it just name and not name*
  if (new_student.student_name == NULL) {
    return 1;//DEFINE
  }
  strcpy(new_student.student_name, name);
  new_student.courses_list = list_init(courses_clone, courses_destroy);
  if (new_student.courses_list == NULL) {
    free(new_student.student_name);
    return 2;//DEFINE
  }
  void *void_new_student = (void*)(&new_student);//check if does what we mean!!
  list_push_back(grades->students, void_new_student);
  free(new_student.student_name);
  list_destroy(new_student.courses_list);
  return 0;
}