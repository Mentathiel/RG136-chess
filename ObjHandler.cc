#include "chess.hpp"
#include <fstream>

void ObjHandler::loadModel(const char* fileName){

    ifstream  file;
    file.open(fileName, ios::in );
    if(file.fail()){
        cout << "Error opening file" << endl;
        exit(EXIT_FAILURE);
    }

    //vector<Vector2f> texture;
    vector<Vector3f> normals;

    vector <string> tokens; 
      
    string intermediate; 
    bool vMode = false;
    //bool vtMode = false;
    bool vnMode = false;
    bool fMode = false;
      
    while(getline(file, intermediate, ' ')) 
    {     
        tokens.push_back(intermediate);
        string type = tokens[0];

        if(type == "v"){
            cout << "v ";
            vMode = true;
        }
        //else if(type == "vt"){
        //    vtMode = true;
        //}
        else if(type == "vn"){
            cout << "vn ";
            vnMode = true;
        }
        else if(type == "f"){
            cout << "f ";
            fMode = true;
        }
        else if(!vMode && /*!vtMode &&*/ !vnMode && !fMode){
            //cout << type << " ";
            vMode = false;
            vnMode = false;
            fMode = false;
            tokens.resize(0);
            continue;
        }

        tokens.erase(tokens.begin());

        if(vnMode){
            float x = stof(tokens[0]);
            float y = stof(tokens[1]);
            float z = stof(tokens[2]);
            vertices.push_back({x,y,z});
        }
        //else if(vtMode){
        //    float x = stof(tokens[0]);
        //    float y = stof(tokens[1]);
        //    texture.push_back({x,y});
        //}
        else if(vnMode){
            float x = stof(tokens[0]);
            float y = stof(tokens[1]);
            float z = stof(tokens[2]);
            normals.push_back({x,y,z});
        }
        else if(fMode){
            normalsOrd.resize(normals.size());

            vector<int> vertex1 = tokenizeF(tokens[0]);
            vector<int> vertex2 = tokenizeF(tokens[1]);
            vector<int> vertex3 = tokenizeF(tokens[2]);

            indices.push_back(vertex1[0]);
            indices.push_back(vertex2[0]);
            indices.push_back(vertex3[0]);

            normalsOrd[vertex1[0]] = normals[vertex1[1]];
            normalsOrd[vertex2[0]] = normals[vertex2[1]];
            normalsOrd[vertex3[0]] = normals[vertex3[1]];
            tokens.resize(0);
            break;
        }

        tokens.resize(0);
    }


    while(getline(file, intermediate, ' ')) 
    {     
        tokens.push_back(intermediate);
        string type = tokens[0];

        if(type == "f"){
            vector<int> vertex1 = tokenizeF(tokens[0]);
            vector<int> vertex2 = tokenizeF(tokens[1]);
            vector<int> vertex3 = tokenizeF(tokens[2]);

            indices.push_back(vertex1[0]);
            indices.push_back(vertex2[0]);
            indices.push_back(vertex3[0]);

            normalsOrd[vertex1[0]] = normals[vertex1[1]];
            normalsOrd[vertex2[0]] = normals[vertex2[1]];
            normalsOrd[vertex3[0]] = normals[vertex3[1]];
        }

        tokens.resize(0);
    }

    file.close();
}

vector<int> ObjHandler::tokenizeF(string s){
    vector<int> res;
    string delimiter = "//";

    size_t pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != string::npos) {
        token = s.substr(0, pos);
        res.push_back(stoi(token));
        s.erase(0, pos + delimiter.length());
    }

    return res;
}

void ObjHandler::draw(){
    glBegin(GL_TRIANGLES);
        for(unsigned i=0; i<indices.size(); i++){
            cout << "vertex" << endl;
            glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
            glNormal3f(vertices[i].x, vertices[i].y, vertices[i].z);
        }
    glEnd();
}