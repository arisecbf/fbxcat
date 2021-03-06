//
//  Node.h
//  libcat
//
//  Created by chenbingfeng on 15/5/15.
//  Copyright (c) 2015年 chenbingfeng. All rights reserved.
//

#ifndef __libcat__Node__
#define __libcat__Node__

#include <memory>
#include <vector>
#include <string>

#include "def.h"
#include "Basewave.h"
#include "Material.h"
#include "Mesh.h"

NS_CAT_BEGIN

typedef struct {
    float translation[3];
    float rotation[4];
    float scale[3];
} Transform;

struct Matrix4x4
{
    float translation[4];
    float rotation[4];
    float scale[4];
    float unknow[4];
};

class Node;
typedef std::weak_ptr<Node> WPNode; //avoid cycle reference

class NodePart: public Basewave
{
public:
    typedef std::shared_ptr<NodePart> SP;
    static SP create();

    void fromJSON(rapidjson::Value& value) override;

private:
    std::string _meshPartId;
    std::string _materialId;
    MeshPart::SP _meshPart;
    Material::SP _material;
    std::vector<std::pair<std::string, Matrix4x4> > _bones;// TODO WPNode
    std::vector<std::vector<int>> _uvMapping; //Texture::SP
    NodePart(){};
};

class Node: public Basewave
{
public:
    typedef std::shared_ptr<Node> SP;
    static SP create(const char* idt = nullptr);
    SP getChild(const char* idt) const;
    bool hasPartsRecurisive() const;
    size_t getTotalNodeCount() const;
    size_t getTotalNodePartCount() const;

    void fromJSON(rapidjson::Value& value) override;

private:
    Transform _transform;
    std::string _id;
    std::vector<NodePart::SP> _parts;
    std::vector<Node::SP> _children;

    Node(const char* idt = nullptr);

};



NS_CAT_END

#endif /* defined(__libcat__Node__) */
