Voici le résultat de notre projet en binôme dans le cadre de l'UE LAOA.

 &emsp; **CLiiCKeR** est un [idle game](https://fr.wikipedia.org/wiki/Jeu_incr%C3%A9mental). Le but de ce type de jeu est d'accumuler le plus possible de ressource/d'argent. Pour se 
faire, pouvons dépenser de cette ressource afin d'acheter des améliorations qui nous permettrons d'en gagner encore plus. Il existe notamment une amélioration commune aux idle 
games qui permet de générer de la ressource automatiquement sur la durée, sans nécessiter d'interventions du jouer, d'où le nome *idle* game.

 &emsp; Le jeu comporte un bouton central *Push Me* qui génère de la ressource aux cliques. Notre ressource actuel, qui correspond donc à notre score est affiché en grand au dessus de 
ce bouton.

 &emsp; Le bouton *Push Me* est placé dans une **tab**, car au cours du jeu, nous pouvons en effet acheter de nouvelles tab. Chaque tab possède son propre set d'objet et d'améliorations, 
et donc son propre taux de ressources par clique. Afin d'acheter une nouvelle fenêtre, il suffit d'appuyer sur le bouton désigné en bas à gauche. Le prix de 
chaque nouvelle fenêtre augmente après chaque achat de fenêtre, et le taux de ressource par clique augmente avec chaque nouvelle fenêtre.    
&emsp;  Lors de la création d'une nouvelle fenêtre, nous devons la nommer. Ce nom nous permet de naviguer plus simplement d'une fenêtre à l'autre lorsque nous en avons beaucoup, grâce
à la barre de recherche située en haut à gauche.

&emsp;  Sur la gauche, nous retrouvons le **panneau d'objets**. Sur ce dernier sont affichés les deux objets disponibles à l'achat, avec pour chacun d'eux indiqués le prix, la quantité,
le prix de l'amélioration, et le niveau d'amélioration. Nous pouvons interragir avec ces objets en en achetant de noouveau, ou en augmentant le niveau d'amélioration. Ces deux
actions coûtent évidemment de la ressource. Ces prix augmentent après chaque utilisation, et plus vite que ce qu'il nous permette de gagner. Cela tend à rendre notre évolution
limitée. Et c'est ici que l'achat de nouvelles tabs prend tous son intérêt, car les quantités et niveuax, comme leurs prix, sont réinitialiser sur chaque nouvelle fenêtre.    
&emsp;  Nous avons implémenter 2 objets:   
&emsp;&emsp;    - *Better Click*, qui permet d'augmenter le taux de ressources par clique;   
&emsp;&emsp;    - *AutoClick*, qui permet d'augmenter le taux de ressources par seconde.   


&emsp;  Le jeu propose de la **manipulation de fichiers**. Les parties peuvent être enregistrées puis chargées à partir de fichiers json. Une sauvegarde contient toutes les informations 
de la partie. Nous avons accès à ces fonctionnalités depuis l'onglet Fichier en haut à gauche, et également grâce aux raccourcis clavier Ctrl-S et Ctrl-O. De la même manière,
nous pouvons créer une nouvelle partie avec l'action "New Game", également accessible avec Ctrl-N. Lorsqu'une partie est en cours, la quitter, ouvrir une partie ou en créer une
une nouvelle fera apparaître un message d'avertissement pour rappeler au joueur qu'il est nécessaire de faire une sauvegarde pour ne pas perde sa progression.
