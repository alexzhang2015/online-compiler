long
get_run_time ()
{
#if defined (HAVE_GETRUSAGE) && defined (HAVE_SYS_RESOURCE_H)
  struct rusage rusage;
  getrusage (0, &rusage);
  return (rusage.ru_utime.tv_sec * 1000000 + rusage.ru_utime.tv_usec
	  + rusage.ru_stime.tv_sec * 1000000 + rusage.ru_stime.tv_usec);
#else /* ! HAVE_GETRUSAGE */
	
	
#ifdef HAVE_TIMES
  struct tms tms;
  times (&tms);
  return (tms.tms_utime + tms.tms_stime) * (1000000 / GNU_HZ);
#else /* ! HAVE_TIMES */
  /* Fall back on clock and hope it's correctly implemented. */
  const long clocks_per_sec = CLOCKS_PER_SEC;
  if (clocks_per_sec <= 1000000)
    return clock () * (1000000 / clocks_per_sec);
  else
    return clock () / clocks_per_sec;

#endif  /* HAVE_TIMES */
#endif  /* HAVE_GETRUSAGE */
}
