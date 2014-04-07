Het license plate detection algoritme in CPP staat onder:
Rik > Code > ImageProcessing > ImageProcessing > ImageProcessing.vcxproj
Je zal even moeten scrollen om "SearchLisenceplateCoordinates" te vinden.

De code voert een Threshold uit voor gele pixels en kijkt of de gevonden 
regio groot genoeg is. Als een kandidaat regio gevonden is worden de 
hoeken gezocht.

Wij (mensen die niet Rik zijn) hebben hem nog niet werkend gekregen.