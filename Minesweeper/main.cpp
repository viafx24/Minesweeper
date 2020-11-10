// rien de particulièrement dur dans ce jeu
// on notera l'utilisation de la souris et la gestion avec deux grilles.
// le code est vraiment court et simple.


#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;

int main()
{
    srand(time(0));

    RenderWindow app(VideoMode(400, 400), "Minesweeper!");

    int w=32; // taille en pixel des cases
    int grid[12][12];// grille sous jacente
    int sgrid[12][12]; //grille qu'on montre j'imagine (s pour show)

    Texture t;
    t.loadFromFile("images/tiles.jpg");
    Sprite s(t);

    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        sgrid[i][j]=10;
        if (rand()%5==0)  grid[i][j]=9; // Une case sur 5 ou sur 6 est une mine (9)?
        else grid[i][j]=0;
      }

    for (int i=1;i<=10;i++)
     for (int j=1;j<=10;j++)
      {
        int n=0;
        if (grid[i][j]==9) continue; // si c'est une mine on sort
        if (grid[i+1][j]==9) n++; // on regarde chaque case adjacente et on incremente n
        if (grid[i][j+1]==9) n++;
        if (grid[i-1][j]==9) n++;
        if (grid[i][j-1]==9) n++;
        if (grid[i+1][j+1]==9) n++;
        if (grid[i-1][j-1]==9) n++;
        if (grid[i-1][j+1]==9) n++;
        if (grid[i+1][j-1]==9) n++;
        grid[i][j]=n; // on sait donc à la fin pour une case donné, combien de mines sont adjacentes: cette valeur c'est n
        // et donc la valeur de la case de la grid est placé à n.
      }

    while (app.isOpen())
    {
        Vector2i pos = Mouse::getPosition(app);

        // la position de la souris est relative à la fenètre certe mais en pixel
        // or nous on veut directement la valeur de la case (x, y) sur laquel pointe la souris
        // on divise donc par la taille d'une case en pixel (32).
        int x = pos.x/w;
        int y = pos.y/w;

        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();

            if (e.type == Event::MouseButtonPressed)
              if (e.key.code == Mouse::Left) sgrid[x][y]=grid[x][y];// on montre la case de grid dans sgrid (la grille qu'on montre)
              else if (e.key.code == Mouse::Right) sgrid[x][y]=11;// avec le clique droit, on met dans sgrid un drapeau sur la case
        }

        // triad clear/draw/display
        app.clear(Color::White);

        for (int i=1;i<=10;i++)
         for (int j=1;j<=10;j++)
          {
             // si le joueur tombe sur une mine, on affiche toute la grille (ca signifie la fin du jeu).
           if (sgrid[x][y]==9) sgrid[i][j]=grid[i][j];

           // tout réside dans ces trois lignes:
           // le sgrid[i][j] va contenir le numero (1,2,3,4...)
           // donc avec ce numero, on vient récupéré le rectangle qu'on veut à la bonne position x de départ sur l'image)
           // la valeur de la texture dans s varie à chaque itération.
           s.setTextureRect(IntRect(sgrid[i][j]*w,0,w,w));

           // on position la case au bon endroit et on dessine.
           s.setPosition(i*w, j*w);
           app.draw(s);
          }

        app.display();
    }

    return 0;
}
