package edu.illinois.cs.cs125.fall2020.mp.models;

/** Rating class for storing client ratings of courses. */
public class Rating {
  /** Rating indicating that the course has not been rated yet. */
  public static final double NOT_RATED = -1.0;

  private String id;
  private double rating;
  /**
   * Rating input is incorrect.
   *
   * @param setId
   * @param setRating
   */
  public Rating(final String setId, final double setRating) {
    id = setId;
    rating = setRating;
  }

  /** empty rating. */
  public Rating() {}

  /**
   * Returns Id as a string.
   *
   * @return returns Id as a string.
   */
  public String getId() {
    return id;
  }

  /**
   * Gets Rating as a double.
   *
   * @return returns the rating as a double.
   */
  public double getRating() {
    return rating;
  }
}
