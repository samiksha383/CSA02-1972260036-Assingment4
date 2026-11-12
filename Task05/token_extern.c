/* Second translation unit defining the shared global token counters */
int global_veg_token = 1000;
int global_nonveg_token = 2000;

int next_global_veg(void)
{
    return ++global_veg_token;
}

int next_global_nonveg(void)
{
    return ++global_nonveg_token;
}
