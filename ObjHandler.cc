#include "chess.hpp"
#include <fstream>
#include <sstream>

ObjHandler::~ObjHandler(){
    for(Vector3f* vertex : vertices)
        delete vertex;
    for(Vector3f* norm : normalsOrd)
        delete norm;
    for(int* ind : indices)
        delete ind;  

    vertices.resize(0);
    //textureOrd.resize(0);
    indices.resize(0);
    normalsOrd.resize(0);
}

void ObjHandler::loadModel(const char* fileName){

    //reset values if reloading
    for(Vector3f* vertex : vertices)
        delete vertex;
    for(Vector3f* norm : normalsOrd)
        delete norm;
    for(int* ind : indices)
        delete ind;

    vertices.resize(0);
    //textureOrd.resize(0);
    indices.resize(0);
    normalsOrd.resize(0);


    ifstream  file;
    file.open(fileName, ios::in );
    if(file.fail()){
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }

    //vector<Vector2f> texture;
    vector<Vector3f*> normals;

    vector<string> lines;
    vector<string> tokens; 

    string intermediate; 
      
    while(getline(file, intermediate)){
        lines.push_back(intermediate);
    }

    for(string line : lines){
        stringstream ss;
        ss << line;
        while(getline(ss, intermediate, ' ')){
            tokens.push_back(intermediate);
        }
    }

/*
    for(unsigned j=0; j<tokens.size(); j++){
        if(tokens[j] == "v")
            cout << "v ";
    }*/

    vector<int*> vertex1;
    vector<int*> vertex2;
    vector<int*> vertex3;
    
    bool vMode = false;
    //bool vtMode = false;
    bool vnMode = false;
    bool fMode = false;

    unsigned i=0;
    for(i=0; i<tokens.size(); i++){

        //cout << tokens[i] << " ";

        if(tokens[i] == "v"){
            //cout << "v ";
            vMode = true;
        }
        //else if(type == "vt"){
        //    vtMode = true;
        //}
        else if(tokens[i] == "vn"){
            //cout << "vn ";
            vnMode = true;
        }
        else if(tokens[i] == "f"){
            //cout << "f ";
            fMode = true;
        }
        else if(!vMode && /*!vtMode &&*/ !vnMode && !fMode){
            //cout << tokens[i] << " ";
            vMode = false;
            vnMode = false;
            fMode = false;
            continue;
        }

        if(vMode){
            float x = stof(tokens[i+1]);
            float y = stof(tokens[i+2]);
            float z = stof(tokens[i+3]);
            vertices.push_back(new Vector3f{x,y,z});
            vMode = false;
        }
        //else if(vtMode){
        //    float x = stof(tokens[i]);
        //    float y = stof(tokens[i+1]);
        //    texture.push_back({x,y});
        //}
        else if(vnMode){
            float x = stof(tokens[i+1]);
            float y = stof(tokens[i+2]);
            float z = stof(tokens[i+3]);
            normals.push_back(new Vector3f{x,y,z});
            vnMode = false;
        }
        else if(fMode){
            fMode = false;

            normalsOrd.resize(vertices.size());

            vertex1 = tokenizeF(tokens[i+1]);
            vertex2 = tokenizeF(tokens[i+2]);
            vertex3 = tokenizeF(tokens[i+3]);

            indices.push_back(vertex1[0]);
            indices.push_back(vertex2[0]);
            indices.push_back(vertex3[0]);

            normalsOrd[*vertex1[0]] = normals[*vertex1[1]];
            normalsOrd[*vertex2[0]] = normals[*vertex2[1]];
            normalsOrd[*vertex3[0]] = normals[*vertex3[1]];

            for(int* i : vertex1)
                delete i;
            for(int* i : vertex2)
                delete i;
            for(int* i : vertex3)
                delete i;

            vertex1.resize(0);
            vertex2.resize(0);
            vertex3.resize(0);

            break;
        }
    }


    for(i=i+1; i<tokens.size(); i++) 
    {
        if(tokens[i] == "f"){
            vertex1 = tokenizeF(tokens[i+1]);
            vertex2 = tokenizeF(tokens[i+2]);
            vertex3 = tokenizeF(tokens[i+3]);

            indices.push_back(vertex1[0]);
            indices.push_back(vertex2[0]);
            indices.push_back(vertex3[0]);

            normalsOrd[*vertex1[0]] = normals[*vertex1[1]];
            normalsOrd[*vertex2[0]] = normals[*vertex2[1]];
            normalsOrd[*vertex3[0]] = normals[*vertex3[1]];


            for(int* i : vertex1)
                if(i != nullptr)
                    delete i;
            for(int* i : vertex2)
                if(i != nullptr)
                    delete i;
            for(int* i : vertex3)
                if(i != nullptr)
                    delete i;

            vertex1.resize(0);
            vertex2.resize(0);
            vertex3.resize(0);          
        }
    }

    file.close();
}

//HACK: Wouldn't work with textures
vector<int*> ObjHandler::tokenizeF(string s){
    vector<int*> res;

    int* a = new int;
    int* b = new int;

    *a = 0;
    *b = 0;

    bool delim = false;
    for(char c : s){
        if(c=='/'){
            delim = true;
            continue;
        }

        if(!delim){
            *a = *a*10 + (c - '0');
        }
        else{
            *b = *b*10 + (c - '0');
        }
    }

    res.push_back(a);
    res.push_back(b);

    return res;
}

void ObjHandler::draw(){
    glBegin(GL_TRIANGLES);
        for(unsigned i=0; i<indices.size(); i++){
            //cout << "vertex" << endl;
            glVertex3f(vertices[i]->x, vertices[i]->y, vertices[i]->z);
            glNormal3f(normalsOrd[i]->x, normalsOrd[i]->y, normalsOrd[i]->z);
        }
    glEnd();
}