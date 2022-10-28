void randFeedHours()
{
  randomSeed(analogRead(0));
  for (int i=0; i<12; i++)
  {
    feedRandHours[i] = random(0, 2);
    feedRandMins[i] = random(0, 2);
  }
}
