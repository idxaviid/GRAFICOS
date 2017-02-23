#define PI 3.14159265359
#include <objecte.h>
#include <readfile.h>
#include <QFile>
Objecte::Objecte(int npoints, QObject *parent) : numPoints(npoints) ,QObject(parent){
    points = new point4[numPoints];
    colors = new point4[numPoints];
    normals = new vec3[numPoints];
    vertexsTextura = new vec2[numPoints];
    //translatedPoints = new point4[numPoints];

    material = new Material();
}

Objecte::Objecte(int npoints, QString n) : numPoints(npoints){
    points = new point4[numPoints];
    colors = new point4[numPoints];
    normals = new vec3[numPoints];
    vertexsTextura = new vec2[numPoints];

    //translatedPoints = new point4[numPoints];
    //dentro de readobj tambien leo el fichero mtl
    readObj(n);
    calculaNormalsVertex();
    make();

    /* esto peta por eso hehecho que si no existe un fichero de material
     * que cree un neuvo material con valores por defecto
    if (!material){
        material = new Material();
    }*/
}


Objecte::~Objecte(){
    delete points;
    delete colors;
}



void Objecte::initTextura()
{
    qDebug() << "Initializing textures...";


    // Carregar la textura
    glActiveTexture(GL_TEXTURE0);
    texture = new QOpenGLTexture(QImage("://resources/textures/earth1.png"));
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    texture->bind(0);

}

void Objecte::initNormalTextura()
{
    glActiveTexture(GL_TEXTURE1);
    normalTexture = new QOpenGLTexture(QImage("://resources/textures/earth3.png"));
    normalTexture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    normalTexture->setMagnificationFilter(QOpenGLTexture::Linear);

    normalTexture->bind(1);

}

/**
 * @brief Objecte::toGPU
 * @param pr
 */
void Objecte::toGPU(QGLShaderProgram *pr) {



    program = pr;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferData( GL_ARRAY_BUFFER, sizeof(point4)*Index + sizeof(vec3)*Index + sizeof(vec2)*Index, NULL, GL_STATIC_DRAW );
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_TEXTURE_2D );
    program->bind();

}


/**
 * Pintat en la GPU.
 * @brief Objecte::draw
 */
void Objecte::draw(){

    // Aqui es torna a repetir el pas de dades a la GPU per si hi ha més d'un objecte
    glBindBuffer( GL_ARRAY_BUFFER, buffer );

    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(point4)*Index, &points[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index, sizeof(vec3)*Index, &normals[0] );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(point4)*Index + sizeof(vec3)*Index, sizeof(vec2)*Index, &vertexsTextura[0] );

    int vertexLocation = program->attributeLocation("vPosition");
    int normalLocation = program->attributeLocation("vNormal");
    int coordTextureLocation = program->attributeLocation("vCoordTexture");



    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4);


    program->enableAttributeArray(normalLocation);
    program->setAttributeBuffer("vNormal", GL_FLOAT, sizeof(vec4)*Index, 3);

    program->enableAttributeArray(coordTextureLocation);
    program->setAttributeBuffer("vCoordTexture", GL_FLOAT, sizeof(vec4)*Index + sizeof(vec3)*Index,2);

    // S'activa la textura i es passa a la GPU
    texture->bind(0);
    program->setUniformValue("texMap", 0);

    texture->bind(1);
    program->setUniformValue("texNormal", 1);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays( GL_TRIANGLES, 0, Index );

    material->toGPU(program);
}

void Objecte::make(){
    static vec3  base_colors[] = {
        vec3( 1.0, 0.0, 0.0 ),
        vec3( 0.0, 1.0, 0.0 ),
        vec3( 0.0, 0.0, 1.0 ),
        vec3( 1.0, 1.0, 0.0 )
    };

    initTextura();


    Index = 0;

    //calculo de minimos y maximos para poder hacer translate
    /*float minX,minY,minZ;
    minX = minY = minZ = 99999.0;
    float maxX,maxY,maxZ;
    maxX = maxY = maxZ = -99999.0;*/
    for(unsigned int i=0; i<cares.size(); i++){
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){

            points[Index] = vertexs[cares[i].idxVertices[j]];
            colors[Index] = vec4(base_colors[j%4], 1.0);
            float u =  0.5 - atan2(normals[Index].z,normals[Index].x)/(2*PI);
            float v =  0.5 - asin(normals[Index].y) / PI;
            vertexsTextura[Index] = vec2(u,v);
            /*
            minX = min(points[Index].x,minX);
            minY = min(points[Index].y,minY);
            minZ = min(points[Index].z,minZ);
            maxX = max(points[Index].x,maxX);
            maxY = max(points[Index].y,maxY);
            maxZ = max(points[Index].z,maxZ);
            */
            Index++;
        }
    }

    /*     Index = 0;
     point4 centre = point4(((minX+maxX)/2),((minY+maxY)/2),((minZ+maxZ)/2),0.0);
     for(unsigned int i=0; i<cares.size(); i++){
         for(unsigned int j=0; j<cares[i].idxVertices.size(); j++){

             translatedPoints[Index] = vertexs[cares[i].idxVertices[j]] - centre;
             float u =  0.5 + atan2(normals[Index].x,normals[Index].z)/(2*PI);
             float v =  0.5 - asin(normals[Index].y) / PI;
             vertexsTextura[Index] = vec2(u,v);
             cout << vertexsTextura[Index] << endl;

             Index++;
         }
     }*/

}

// Llegeix un fitxer .obj
//  Si el fitxer referencia fitxers de materials (.mtl), encara no es llegeixen
//  Tots els elements del fitxer es llegeixen com a un unic objecte.
void Objecte::readObj(QString filename){

    FILE *fp = fopen(filename.toLocal8Bit(),"rb");
    if (!fp)
    {
        cout << "No puc obrir el fitxer " << endl;
    }
    else {

        while (true)
        {
            char *comment_ptr = ReadFile::fetch_line (fp);

            if (comment_ptr == (char *) -1)  /* end-of-file */
                break;

            /* did we get a comment? */
            if (comment_ptr) {
                //make_comment (comment_ptr);
                continue;
            }

            /* if we get here, the line was not a comment */
            int nwords = ReadFile::fetch_words();

            /* skip empty lines */
            if (nwords == 0)
                continue;

            char *first_word = ReadFile::words[0];

            if (!strcmp (first_word, "v"))
            {
                if (nwords < 4) {
                    fprintf (stderr, "Too few coordinates: '%s'", ReadFile::str_orig);
                    exit (-1);
                }

                QString sx(ReadFile::words[1]);
                QString sy(ReadFile::words[2]);
                QString sz(ReadFile::words[3]);
                double x = sx.toDouble();
                double y = sy.toDouble();
                double z = sz.toDouble();

                if (nwords == 5) {
                    QString sw(ReadFile::words[4]);
                    double w = sw.toDouble();
                    x/=w;
                    y/=w;
                    z/=w;
                }
                // S'afegeix el vertex a l'objecte
                vertexs.push_back(point4(x, y, z, 1));

            }
            else if (!strcmp (first_word, "vn")) {
            }
            else if (!strcmp (first_word, "vt")) {
            }
            else if (!strcmp (first_word, "f")) {
                // S'afegeix la cara a l'objecte
                // A modificar si es vol carregar mes de un objecte
                construeix_cara (&ReadFile::words[1], nwords-1);
            }
            // added
            else if (!strcmp (first_word, "mtllib")) {
                //read_mtllib (&words[1], nwords-1, matlib, filename);
            }
            else if (!strcmp (first_word, "usemtl")) {
                //int size = strlen(words[1])-1;
                //while (size && (words[1][size]=='\n' || words[1][size]=='\r') ) words[1][size--]=0;
                //currentMaterial = matlib.index(words[1]);
            }
            // fadded
            else {
                //fprintf (stderr, "Do not recognize: '%s'\n", str_orig);
            }
        }
    }
    //leo fichero mtl, tiene que tener el mismo nombre que el obj pero extension mtl
    readMtl(filename.replace("obj","mtl"));

}
void Objecte::readMtl(QString fileName){
    //Material m = new Material();

    QFile inputFile(fileName);
    if (inputFile.open(QIODevice::ReadOnly))
    {
        QTextStream in(&inputFile);

        vec3 Ka = vec3(0.0);
        vec3 Kd = vec3(0.0);
        vec3 Ks = vec3(0.0);
        float S = 0.0;



        while (!in.atEnd())
        {
            QString line = in.readLine();
            float vec[4];//Creo vector para guardar datos auxiliares
            std::list<QString> l = line.split(' ').toStdList();
            for (int i = 0;i <= l.size();i++){
                QString s = l.back();
                l.pop_back();
                vec[i] = s.toFloat();
            }
            if (line.contains("Ns"))
            {
                S = vec[0];
            }
            else if(line.contains("Ks"))
            {
                Ks.x = vec[2];
                Ks.y = vec[1];
                Ks.z = vec[0];
            }
            else if (line.contains("Kd"))
            {
                Kd.x = vec[2];
                Kd.y = vec[1];
                Kd.z = vec[0];
            }
            else if (line.contains("Ka"))
            {
                Ka.x = vec[2];
                Ka.y = vec[1];
                Ka.z = vec[0];
            }

        }
        inputFile.close();
        cout << "El material leido desde .mtl es: Ka" << Ka <<" Kd"<< Kd << " Ks"<< Ks <<" Shininess "<< S << endl;
        material = new Material(Ka,Kd,Ks,S,1);
    }else{
        //Si no existe fichero con material creo un nuevo material con los valores por defecto
        cout << "Fichero .mtl de material no encontrado aplicando material por defecto" << endl;
        material = new Material();
    }



}

void Objecte::construeix_cara ( char **words, int nwords) {
    Cara face;

    for (int i = 0; i < nwords; i++) {
        int vindex;
        int nindex;
        int tindex;

        if ((words[i][0]>='0')&&(words[i][0]<='9')) {
            ReadFile::get_indices (words[i], &vindex, &tindex, &nindex);

#if 0
            printf ("vtn: %d %d %d\n", vindex, tindex, nindex);
#endif

            /* store the vertex index */

            if (vindex > 0)       /* indices are from one, not zero */
                face.idxVertices.push_back(vindex - 1);
            else if (vindex < 0)  /* negative indices mean count backwards */
                face.idxVertices.push_back(this->vertexs.size() + vindex);
            else {
                fprintf (stderr, "Zero indices not allowed: '%s'\n", ReadFile::str_orig);
                exit (-1);
            }
        }
    }
    face.color = vec4(1.0, 0.0, 0.0, 1.0);
    this->cares.push_back(face);
}

void Objecte::calculaNormalsVertex(){

    Index=0;
    vector <float> points_idxVec;
    vector <vec3 * > vec_normals (vertexs.size());

    //para cada cara
    for(unsigned int idCara=0; idCara<cares.size(); idCara++)
    {
        //Calculo la normal de la cara
        cares[idCara].calculaNormal(vertexs);

        //Para cada vertice de la cara actual
        for(unsigned int idVertex=0; idVertex<cares[idCara].idxVertices.size(); idVertex++)
        {
            points[Index] = vertexs[cares[idCara].idxVertices[idVertex]];

            //Meto la id del vertice en un array de ids de vertises
            points_idxVec.push_back(cares[idCara].idxVertices[idVertex]);
            Index++;
            // si no hay normales creo normal nueva
            if (!vec_normals[cares[idCara].idxVertices[idVertex]]){
                vec_normals[cares[idCara].idxVertices[idVertex]] = new vec3(cares[idCara].normal);
            }else{//si hay la sumo
                vec_normals[cares[idCara].idxVertices[idVertex]]->operator += (cares[idCara].normal);
            }

        }
    }

    //hago media de las normales
    for (unsigned int i=0; i<Index; ++i)
    {
        normals[i] = *vec_normals[points_idxVec[i]] / length((*vec_normals[points_idxVec[i]]));
        //cout<<normals[i]<<endl;
    }


    //------------------------ FLAT (normal x cada cara, no por cada vertice) --------------------------------------------

    /*Index = 0;
    for(unsigned int i=0; i<cares.size(); i++)
    {
        for(unsigned int j=0; j<cares[i].idxVertices.size(); j++)
        {
            points[Index] = vertexs[cares[i].idxVertices[j]];
            cares[i].calculaNormal(vertexs);
            normals[Index] = cares[i].normal;
            Index++;
        }
    }*/

    //-----------------------------------------------------------------------

}



