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
struct student* list_search_id(struct grades *grades ,int check_id);
int course_exist(struct student *student ,const char *check_name);
int print_courses(struct student *print_student_course);

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
    void *get_iterator = list_get(iterator);
    if (get_iterator == NULL) {
      free(new_student->student_name);
      free(new_student);
    }// should we check if get_iterator is just a NULL or something else???
    int x = list_insert(new_student->courses_list,
                        it_last_grade_new_student,
                        get_iterator);
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

struct student *list_search_id(struct grades *grades ,int check_id) {
  pnode_t iterator = list_begin(grades->students);
  while (iterator != NULL) {
    struct student *current_student = (struct student *)list_get(iterator);
    if (current_student == NULL) {
      return NULL;
    }
    int current_id = current_student->id;
    if (check_id == current_id) {
      return current_student;
    }
    iterator = list_next(iterator);
  }
  return NULL;
}

int course_exist(struct student *student ,const char *check_name) {
  pnode_t iterator = list_begin(student->courses_list);
  while (iterator != NULL) {
    struct courses *current_course = (struct courses *)list_get(iterator);
    if (current_course == NULL) {
      return 1;
    }
    char *current_course_name = current_course->course_name;
    if (strcmp(current_course_name, check_name) == 0) {
      return 0;
    }
    iterator = list_next(iterator);
  }
  return 2;
}
int print_courses(struct student *print_student_course) {
  pnode_t iterator = list_begin(print_student_course->courses_list);
  struct courses *course_to_print;
  while(iterator){
    course_to_print = (struct courses *)list_get(iterator);
    if (course_to_print == NULL) {
      return 1;
    }
    printf("%s %d, ", course_to_print->course_name, course_to_print->grade);
    iterator = list_next(iterator);
  }
  printf("\n");
  return 0;
}
/**
struct student new_student( const char *student_name, int id){
  struct courses new_course;
  new_course.grade = grade;
  new_course.course_name = (char *) malloc(strlen(student_name) + 1); //not sure
  // why is it just name and not name*
  if (new_course.course_name == NULL) {
    return 5;//DEFINE
  }
  strcpy(new_course.course_name, student_name);
}

struct courses new_course(const char *course_name, int grade){
  struct courses new_course;
  new_course.grade = grade;
  new_course.course_name = (char *) malloc(strlen(course_name) + 1); //not sure
  // why is it just name and not name*
  if (new_course.course_name == NULL) {
    return ;//DEFINE
  }
  strcpy(new_course.course_name, course_name);
}
 */
////////////////////////////////////////////////
/////////////////grades.h functions/////////////
////////////////////////////////////////////////
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

int grades_print_student(struct grades *grades, int id) {

  if (grades->students == NULL) {
    return 1; //DEFINE
  }
  struct student *student_to_print = (list_search_id(grades ,id));
  if (student_to_print == NULL) {
    return 2;//DEFINE!!
  }
  printf("%s %d: ", student_to_print->student_name, id);///without course name
  // and
  // grade!!!!!!
  int print_success = print_courses(student_to_print);
  if (print_success != 0) {
    return 3;
  }else {
    return 0;
  }
}

int grades_print_all(struct grades *grades) {
  pnode_t iterator = list_begin(grades->students);
  while (iterator != NULL) {
    struct student *current_student = (struct student *)list_get(iterator);
    if (current_student == NULL) {
      return 1;
    }
    printf("%s %d: ", current_student->student_name, current_student->id);
    iterator = list_next(iterator);
    int print_success = print_courses(current_student);
    if (print_success != 0) {
      return 3;
    }
  }
  return 0;
}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){
  if (grade<0 || grade>100){
    return 1;
  }
  struct student *student_to_add_grade = list_search_id(grades ,id);
  if (student_to_add_grade == NULL) {
    return 2;//DEFINE!!
  }else if (course_exist(student_to_add_grade, name) == 0){
    return 3;
  }else if (grades->students == NULL) {
    return 4; //DEFINE
  }

  struct courses new_course;
  new_course.grade = grade;
  new_course.course_name = (char *) malloc(strlen(name) + 1); //not sure
  // why is it just name and not name*
  if (new_course.course_name == NULL) {
    return 5;//DEFINE
  }
  strcpy(new_course.course_name, name);
  void *void_new_course = (void*)(&new_course);//check if does what we mean!!
  if(list_push_back(student_to_add_grade->courses_list, void_new_course) !=0){
    //who should free all the lists?
    return 6;
  }
  free(new_course.course_name);
  return 0;
}
