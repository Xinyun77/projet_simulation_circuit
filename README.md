L’objectif de ce projet est de se familiariser à la modélisation objet au travers la
construction de classes, de manipuler les conteneurs de la STL (standard template library),
et de mettre en oeuvre le polymorpisme (un appel à une fonction membre entraînera l’exécution 
d’une fonction différente en fonction du type d’objet qui appelle la fonction) en C++.

On souhaite disposer d’un outil de simulation numérique permettant de simuler les transi-
toires électromagnétiques dans les réseaux électriques. Pour cela, comme énoncé précédemment,
nous modélisons ce réseau comme un circuit constitué d’une liste de composants électriques
élémentaires.
Chaque composant peut être vu de manière générique comme un objet de type Nports.
Ces compososants sont modélisés par la création de classes

La notion de classe généralise celle des structures.
Les classes que nous utilisons pour la modélisation des composants élémentaires se veulent
toutes canoniques, c’est-à-dire qu’elles comportent toutes au minimum :
1. Un contructeur par défaut : permet aux objets construits sans arguments de possèder,
par défaut, une valeur que l’on déternime
2. Un constructeur par copie : permet la création d’un objet à partir d’un autre pris comme
modèle
3. Un destructeur (virtuel) : permet de libérer l’espace mémoire occupée par un objet
lorsqu’il arrive en fin de vie
4. Un opérateur d’affectation : par la surchage de l’opérateur =, elle est utilisée pour copier
un objet dans un autre en dehors des déclarations

**Principe de construction **:
Circuit en dérivation
La matrice d’admittance modélise pour chaque composant et chaque nœud du circuit, les
entrées et sorties de courant qui y sont rattachés.
La construction d’un telle matrice se fait selon les principes énoncés dans les lois de Kir-
chhoff :
— Loi des mailles : La somme algébrique des tensions le long d’une maille est nulle.
— Loi des nœuds : La somme algébrique des courants à un nœud est nulle. Les courants
sont comptés positivement quand ils entrent dans un nœud.
Notons Nc le nombre de composants (sans compter le composant de Mise à la terre) et Nnode
le nombre de noeuds du circuit.
La matrice est construite telle que :
— Il y a 2 × Nc + Nnode lignes, et autant de colonnes
— Les Nc premières lignes concernent les tensions (loi des mailles)
— Les lignes suivantes concernent les courants (loi des nœuds)
En effet, pour chaque composant, on considère d’abord l’équation engendrée par la tension
à ses bornes en fonction de sa position, ensuite on s’intéresse aux équations engendrées par les
courants entrant dans les nœuds.
Le courant et la tension sont ici des grandeurs qui oscillent avec une certaine fréquence f
fixée.
Dans l’analyse en courant alternatif les sources de tension ou les sources de courant, on définit
la fréquence angulaire ω = 2πf à partir de cette fréquence.
Ensuite, avec une représentation dîte phaseur où j2 = −1, on note le courant et la tension en
fonction du temps sous forme complexe, comme étant :
i(t) =  ̄iejωt,  ̄i ∈ C,
v(t) =  ̄vejωt,  ̄v ∈ C.
Les voltages et les courants sont donc les Re( ̄vejωt) et Re( ̄iejωt). On approxime également par
le complexe Eejωt la source de voltage pour représenter la partie réelle E cos(ωt).
