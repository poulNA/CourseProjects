package edu.illinois.cs.cs125.fall2020.mp.models;

/** Class Course extends Summary and holds description. */
public class Course extends Summary {
  private String description;

  /** Create an empty Course. */
  @SuppressWarnings({"unused", "RedundantSuppression"})
  public Course() {}
  /**
   * create a course with provided field.
   *
   * @param setDescription
   */
  public Course(final String setDescription) {
    description = setDescription;
  }

  /**
   * Get the description for the course.
   *
   * @return the description for this Course
   */
  public String getDescription() {
    return description;
  }
}
