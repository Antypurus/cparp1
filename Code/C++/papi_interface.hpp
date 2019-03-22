namespace papi{
void handle_error (int retval);

void init_papi();

int start_using();

void stop_using(int events);

void start_measure(int events);

void stop_measure(int events);
}