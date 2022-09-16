void randFeedHours()
{
  randomSeed(analogRead(0));
  for (int i=0; i<12; i++)
  {
    int rn = random(0, 2);
    feedRandHours[i] = rn;
    feedRandMins[i] = rn;
  }
}
