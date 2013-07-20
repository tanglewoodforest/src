#ifndef twf_track_h
#define twf_track_h


class track_data
{
public:
  track_data*   next;
  int           race;
  int           to_dir;
  long          decay_time;

  track_data( );
  ~track_data( );
};


#endif // twf_track_h
