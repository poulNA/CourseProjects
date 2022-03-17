package edu.illinois.cs.cs125.fall2020.mp.activities;

import android.content.Intent;
import android.os.Bundle;
import android.widget.RatingBar;


import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.databinding.DataBindingUtil;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.ObjectMapper;
import edu.illinois.cs.cs125.fall2020.mp.R;
import edu.illinois.cs.cs125.fall2020.mp.application.CourseableApplication;
import edu.illinois.cs.cs125.fall2020.mp.databinding.ActivityCourseBinding;
import edu.illinois.cs.cs125.fall2020.mp.models.Course;
import edu.illinois.cs.cs125.fall2020.mp.models.Rating;
import edu.illinois.cs.cs125.fall2020.mp.models.Summary;
import edu.illinois.cs.cs125.fall2020.mp.network.Client;

/** Course activity showing the course description. */
public class CourseActivity extends AppCompatActivity implements Client.CourseClientCallbacks {
  private Summary deserialized;
  private static final String TAG = CourseActivity.class.getSimpleName();

  // Binding to the layout in activity_course.xml
  private ActivityCourseBinding binding;
  /**
   * Called when this course activity is clicked.
   *
   * @param savedInstanceState saved instance state
   */
  @Override
  public void onCreate(@Nullable final Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    Intent intent = getIntent();
    ObjectMapper mapper = new ObjectMapper();
    mapper.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);
    binding = DataBindingUtil.setContentView(this, R.layout.activity_course);
    try {
      deserialized = mapper.readValue(intent.getStringExtra("COURSE"), Summary.class);
      CourseableApplication application = (CourseableApplication) getApplication();
      application.getCourseClient().getCourse(deserialized, this);
      application.getCourseClient().getRating(deserialized, application.getClientID(), this);
      binding.rating.setOnRatingBarChangeListener((final RatingBar ratingBar1,
                                                   final float rating2, final boolean fromUser) -> {
        Rating object = new Rating(application.getClientID(), rating2);
        application.getCourseClient().postRating(deserialized, object, this);
      });
    } catch (JsonProcessingException e) {
      e.printStackTrace();
    }
  }
  /**
   * Return courses.
   *
   * @param summary a course summary
   * @param course a course
   */
  @Override
  public void courseResponse(final Summary summary, final Course course) {
    binding.textview.setText(course.getDescription());
    binding.textview1.setText(course.getTitle());
  }

  /**
   * changes rating.
   * @param summary
   * @param rating3
   */
  @Override
  public void yourRating(final Summary summary, final Rating rating3) {
    binding.rating.setRating((float) rating3.getRating());
  }
}
