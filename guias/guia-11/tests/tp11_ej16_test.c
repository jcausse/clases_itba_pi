#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "phrasesADT.h"
#include <assert.h>

int main(void) {
    assert(newPhrasesADT(1200, 1100)==NULL);
    phrasesADT p = newPhrasesADT(1200, 1800);
    assert(p!=NULL);
    assert(put(p, 1199, "Hello" )==0);
    assert(size(p)==0);
    assert(put(p, 1200, "Hello" )==1);
    assert(put(p, 1210, ", " )==1);
    assert(put(p, 1220, "world" )==1);
    assert(size(p)==3);
    
    char * aux = get(p, 1100);
    assert(aux==NULL);
    aux= get(p, 1200);
    assert(strcmp(aux, "Hello")==0);
    free(aux);
    aux= get(p, 1210);
    assert(strcmp(aux, ", ")==0);
    free(aux);
    aux= get(p, 1220);
    assert(strcmp(aux, "world")==0);
    free(aux);
    
    aux = concatAll(p);
    assert(strcmp(aux, "Hello, world")==0);
    free(aux);
    
    aux = concat(p,1230, 1800);
    assert(strcmp(aux, "")==0);
    free(aux);
    
    aux = concat(p,1200, 1800);
    assert(strcmp(aux, "Hello, world")==0);
    free(aux);
    
    // reemplazamos "world" por otro texto
    assert(put(p, 1220, "mundo cruel." )==1);
    assert(size(p)==3);
    aux = concatAll(p);
    assert(strcmp(aux, "Hello, mundo cruel.")==0);
    free(aux);
    freePhrases(p);
 
    p = newPhrasesADT(1, 20);   
    put(p,1, "On the burning February morning Beatriz Viterbo died, after braving an agony that never for a single moment gave way to self-pity or fear, "
    "I noticed that the sidewalk billboards around Constitution Plaza were advertising some new brand or other of American cigarettes. "
    "The fact pained me, for I realised that the wide and ceaseless universe was already slipping away from her and that this slight change "
    "was the first of an endless series. The universe may change but not me, I thought with a certain sad vanity. "
    "I knew that at times my fruitless devotion had annoyed her; now that she was dead, I could devote myself to her memory, "
    "without hope but also without humiliation. I recalled that the thirtieth of April was her birthday; on that day to visit her house on Garay Street "
    "and pay my respects to her father and to Carlos Argentino Daneri, her first cousin, would be an irreproachable and perhaps unavoidable act of politeness. "
    "Once again I would wait in the twilight of the small, cluttered drawing room, once again I would study the details of her many photographs: "
    "Beatriz Viterbo in profile and in full colour; Beatriz wearing a mask, during the Carnival of 1921; "
    "Beatriz at her First Communion; Beatriz on the day of her wedding to Roberto Alessandri; "
    "Beatriz soon after her divorce, at a luncheon at the Turf Club; Beatriz at a seaside resort in Quilmes with Delia San Marco Porcel and Carlos Argentino; "
    "Beatriz with the Pekingese lapdog given her by Villegas Haedo; Beatriz, front and three-quarter views, smiling, hand on her chin... "
    "I would not be forced, as in the past, to justify my presence with modest offerings of books -- books whose pages I finally learned to cut beforehand, "
    "so as not to find out, months later, that they lay around unopened.");
    
    put(p,2, "Beatriz Viterbo died in 1929. From that time on, I never let a thirtieth of April go by without a visit to her house. "
    "I used to make my appearance at seven-fifteen sharp and stay on for some twenty-five minutes. "
    "Each year, I arrived a little later and stay a little longer. In 1933, a torrential downpour coming to my aid, "
    "they were obliged to ask me for dinner. Naturally, I took advantage of that lucky precedent. "
    "In 1934, I arrived, just after eight, with one of those large Santa Fe sugared cakes, and quite matter-of-factly I stayed to dinner. "
    "It was in this way, on these melancholy and vainly erotic anniversaries, that I came into the gradual confidences of Carlos Argentino Daneri." );
    
    put(p,3, "Be thou as chaste as ice, as pure as snow, thou shalt not escape calumny. Get thee to a nunnery, go.");
    assert(size(p)==3);
    
    put(p,10, "On the burning February morning Beatriz Viterbo died, after braving an agony that never for a single moment gave way to self-pity or fear, "
    "I noticed that the sidewalk billboards around Constitution Plaza were advertising some new brand or other of American cigarettes. "
    "The fact pained me, for I realised that the wide and ceaseless universe was already slipping away from her and that this slight change "
    "was the first of an endless series. The universe may change but not me, I thought with a certain sad vanity. "
    "I knew that at times my fruitless devotion had annoyed her; now that she was dead, I could devote myself to her memory, "
    "without hope but also without humiliation. I recalled that the thirtieth of April was her birthday; on that day to visit her house on Garay Street "
    "and pay my respects to her father and to Carlos Argentino Daneri, her first cousin, would be an irreproachable and perhaps unavoidable act of politeness. "
    "Once again I would wait in the twilight of the small, cluttered drawing room, once again I would study the details of her many photographs: "
    "Beatriz Viterbo in profile and in full colour; Beatriz wearing a mask, during the Carnival of 1921; "
    "Beatriz at her First Communion; Beatriz on the day of her wedding to Roberto Alessandri; "
    "Beatriz soon after her divorce, at a luncheon at the Turf Club; Beatriz at a seaside resort in Quilmes with Delia San Marco Porcel and Carlos Argentino; "
    "Beatriz with the Pekingese lapdog given her by Villegas Haedo; Beatriz, front and three-quarter views, smiling, hand on her chin... "
    "I would not be forced, as in the past, to justify my presence with modest offerings of books -- books whose pages I finally learned to cut beforehand, "
    "so as not to find out, months later, that they lay around unopened."
    "Beatriz Viterbo died in 1929. From that time on, I never let a thirtieth of April go by without a visit to her house. "
    "I used to make my appearance at seven-fifteen sharp and stay on for some twenty-five minutes. "
    "Each year, I arrived a little later and stay a little longer. In 1933, a torrential downpour coming to my aid, "
    "they were obliged to ask me for dinner. Naturally, I took advantage of that lucky precedent. "
    "In 1934, I arrived, just after eight, with one of those large Santa Fe sugared cakes, and quite matter-of-factly I stayed to dinner. "
    "It was in this way, on these melancholy and vainly erotic anniversaries, that I came into the gradual confidences of Carlos Argentino Daneri.");
    
    aux = get(p, 2);
    assert(strncmp(aux,"Beatriz Viterbo",15 )==0);
    
    assert(strlen(aux)==690);
    
    char *aux1 = get(p, 1);
    
    char aux12[strlen(aux1)+strlen(aux)+1];
    strcpy(aux12, aux1);
    strcat(aux12, aux);
    
    char * aux10 = get(p,10);
    assert(strcmp(aux12, aux10)==0);
    
    free(aux);
    free(aux1);
    free(aux10);
    
    freePhrases(p);
    puts("OK!");
    return 0;
}