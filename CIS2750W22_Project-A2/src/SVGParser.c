/*
Name: Simardeep Singh
School ID: 1129156
*/

#include "LinkedListAPI.h"
#include "SVGParser.h"
#include <ctype.h>
#include <math.h>

// prototypes of the helper functions used in the assignment
Attribute *attribe(xmlAttr *attr);
Rectangle *rectangle(xmlNode *a_node);
Circle *circle(xmlNode *cur_node);
Path *pather(xmlNode *cur_node);
Group *grouper(xmlNode *cur_node);
char *retrieveData(char *retrieveVal);
void assistGp(Group *gP, List *elements);
void titleDescTree(xmlNodePtr root, const SVG* svg);
void attTree(xmlNodePtr root_node, List* tempList);
void RCPTree(xmlNodePtr root_node, List* rects, List* circles, List * paths);
void groupTree(xmlNodePtr root_node, List*);
void update(Attribute* newAttribute, List* list);
int validHelp(const SVG* img);
int validAtr(List* list);



// Store the attributes of the element in the string format
char *attributeToString(void *data)
{
    char *tmpStr;
    Attribute *atr;
    int len;
    if (data == NULL)
    {
        return NULL;
    }
    atr = (Attribute *)data; // typecast into Attribute
    len = strlen(atr->name) + strlen(atr->value) + 5;
    tmpStr = (char *)malloc(sizeof(char) * len);       // dynamic memory allocation
    sprintf(tmpStr, "%s : %s", atr->name, atr->value); // store string in the specified format
    return tmpStr;
}
/** Function to converting a JSON string into an SVG struct
*@pre JSON string is not NULL
*@post String has not been modified in any way
*@return A newly allocated and initialized SVG struct
*@param str - a pointer to a string
**/
SVG* JSONtoSVG(const char* svgString)
{
    return NULL;
}

/** Function to converting a JSON string into a Rectangle struct
*@pre JSON string is not NULL
*@post Rectangle has not been modified in any way
*@return A newly allocated and initialized Rectangle struct
*@param str - a pointer to a string
**/
Rectangle* JSONtoRect(const char* svgString)
{
    return NULL;
}

/** Function to converting a JSON string into a Circle struct
*@pre JSON string is not NULL
*@post Circle has not been modified in any way
*@return A newly allocated and initialized Circle struct
*@param str - a pointer to a string
**/
Circle* JSONtoCircle(const char* svgString)
{
    return NULL;
}
// Store the rectangle attributes in the string format
char *rectangleToString(void *data)
{
    char *tmpStr;
    int len;
    Rectangle *atr;
    if (data == NULL)
    {
        return NULL;
    }
    atr = (Rectangle *)data; // typecast into Rectangle
    char *printRect = toString(atr->otherAttributes);
    len = strlen(printRect) + strlen(atr->units) + 141;
    tmpStr = (char *)malloc(sizeof(char) * len); // dynamically allocate the memory

    sprintf(tmpStr, "x : %f\ny : %f\nwidth : %f\nheight : %f\nunits : %s\nOther Attributes : %s", atr->x, atr->y, atr->width, atr->height, atr->units, printRect); // store string in the specified format
    free(printRect);                                                                                                                                               // free the memory of toString function called earlier
    return tmpStr;
}
// Store the circle attributes in the string format
char *circleToString(void *data)
{
    char *tmpStr;
    int len;
    Circle *atr;
    if (data == NULL)
    {
        return NULL;
    }
    atr = (Circle *)data;
    char *printCircle = toString(atr->otherAttributes);
    len = strlen(printCircle) + strlen(atr->units) + 109;
    tmpStr = (char *)malloc(sizeof(char) * len); // dynamically allocated memory

    sprintf(tmpStr, "cx : %f\ncy : %f\nr : %f\nunits : %s\nOther Attributes : %s", atr->cx, atr->cy, atr->r, atr->units, printCircle); // store string in the specified format
    free(printCircle);                                                                                                                 // free the memory of toString function called earlier
    return tmpStr;
}
// Store the path attributes in the string format
char *pathToString(void *data)
{
    char *tmpStr;
    int len;
    Path *atr;
    if (data == NULL)
    {
        return NULL;
    }
    atr = (Path *)data;
    char *printPath = toString(atr->otherAttributes);
    len = strlen(printPath) + strlen(atr->data) + 30;
    tmpStr = (char *)malloc(sizeof(char) * len);                               // dynamically allocated memory
    sprintf(tmpStr, "Data : %s\nOther Attributes : %s", atr->data, printPath); // store string in the specified format

    free(printPath); // free the memory of toString function called earlier
    return tmpStr;
}
// Store the group attributes in the string format
char *groupToString(void *data)
{
    char *tmpStr;
    int len;
    Group *atr;

    if (data == NULL)
    {
        return NULL;
    }
    atr = (Group *)data;
    char *gpPath = toString(atr->paths);
    char *gpRect = toString(atr->rectangles);
    char *gpCirc = toString(atr->circles);
    char *gpGp = toString(atr->groups);
    char *printGp = toString(atr->otherAttributes);

    len = strlen(gpPath) + strlen(gpCirc) + strlen(gpGp) + strlen(printGp) + strlen(gpRect) + 62;
    tmpStr = (char *)malloc(sizeof(char) * len); // dynamically allocate the memory

    sprintf(tmpStr, "Rectangle : %s\nPath : %s\nCircle : %s\nGroup : %s\nOther Attributes : %s\n", gpRect, gpPath, gpCirc, gpGp, printGp); // store the string in the specified formqt
    // free all the memories of the toString function called
    free(printGp);
    free(gpPath);
    free(gpRect);
    free(gpCirc);
    free(gpGp);
    return tmpStr;
}

// delete the attributes
void deleteAttribute(void *data)
{
    Attribute *tmpName;
    if (data == NULL)
    {
        return;
    }
    tmpName = (Attribute *)data; // typecast into Attribute
    free(tmpName->name);         // free the name
    free(tmpName);               // free the Attribute struct
}
// delete the rectangle and all its attributes
void deleteRectangle(void *data)
{
    Rectangle *tmpName;
    if (data == NULL)
    {
        return;
    }
    tmpName = (Rectangle *)data;        // typcast to Rectangle type of Struct
    freeList(tmpName->otherAttributes); // free the list of rectangle attributes
    free(tmpName);                      // free the rectangle list
}
// delete the circle and all its attributes
void deleteCircle(void *data)
{
    Circle *tmpName;
    if (data == NULL)
    {
        return;
    }
    tmpName = (Circle *)data;           // typecast to Circle type of struct
    freeList(tmpName->otherAttributes); // free the lis t of circle attributes
    free(tmpName);                      // free the circle list
}
// delete the path and all its attributes
void deletePath(void *data)
{
    Path *tmpName;
    if (data == NULL)
    {
        return;
    }
    tmpName = (Path *)data;             // typecast to path type of struct
    freeList(tmpName->otherAttributes); // free the list of the path attributes
    free(tmpName);                      // free the path list
}
// delete the group and its elements along with their attributes
void deleteGroup(void *data)
{
    Group *tmpName;
    if (data == NULL)
    {
        return;
    }
    tmpName = (Group *)data;
    freeList(tmpName->otherAttributes); // free the list of otherattributes
    freeList(tmpName->rectangles);      // free the list of rectangles
    freeList(tmpName->circles);         // free the list of circles
    freeList(tmpName->paths);           // free the list of paths
    freeList(tmpName->groups);          // free the list of groups
    free(tmpName);                      // free the list of groups
}

// various compare function stubs
int compareAttributes(const void *first, const void *second)
{
    return 0;
}

int compareRectangles(const void *first, const void *second)
{
    return 0;
}

int compareCircles(const void *first, const void *second)
{
    return 0;
}

int comparePaths(const void *first, const void *second)
{
    return 0;
}

int compareGroups(const void *first, const void *second)
{
    return 0;
}
// find and store title and description of the element
void titleDesc(xmlNode *a_node, SVG *svgFile)
{
    xmlNode *cur_node = NULL;
    for (cur_node = a_node; cur_node != NULL; cur_node = cur_node->next)
    { // store the title
        if (strcmp((const char *)cur_node->name, "title") == 0)
        {
            if (cur_node->children->content != NULL)
            {
                strcpy(svgFile->title, (const char *)cur_node->children->content);
            }
        } // store the description
        if (strcmp((const char *)cur_node->name, "desc") == 0)
        {
            if (cur_node->children->content != NULL)
            {
                strcpy(svgFile->description, (const char *)cur_node->children->content);
            }
        }
    }
}
// Function to create an SVG struct based on the contents of an SVG file.
SVG *createSVG(const char *fileName)
{ // if file doesn't exist, return NULL
    if (fileName == NULL)
    {
        return NULL;
    }
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    LIBXML_TEST_VERSION

    SVG *svgFile = (SVG *)malloc(sizeof(SVG));
    doc = xmlReadFile(fileName, NULL, 0);
    // if failed to parse, return NULL
    if (doc == NULL)
    {
        return NULL;
    }

    root_element = xmlDocGetRootElement(doc); // point to root node

    svgFile->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);
    svgFile->rectangles = initializeList(rectangleToString, deleteRectangle, compareRectangles);
    svgFile->circles = initializeList(circleToString, deleteCircle, compareCircles);
    svgFile->paths = initializeList(pathToString, deletePath, comparePaths);
    svgFile->groups = initializeList(groupToString, deleteGroup, compareGroups);
    strcpy(svgFile->namespace, "");
    strcpy(svgFile->description, "");
    strcpy(svgFile->title, "");
    strcpy(svgFile->namespace, (char *)root_element->ns->href);
    titleDesc(root_element->children, svgFile);
    // iterate through all nodes
    for (xmlNode *cur_node = root_element->children; cur_node != NULL; cur_node = cur_node->next)
    { // deal with rectnagles
        if (strcmp((const char *)cur_node->name, "rect") == 0)
        {
            Rectangle *rectFile = rectangle(cur_node);
            insertBack(svgFile->rectangles, rectFile);
        } // deal with circles
        if (strcmp((const char *)cur_node->name, "circle") == 0)
        {
            Circle *circFile = circle(cur_node);
            insertBack(svgFile->circles, circFile);
        } // deal with paths
        if (strcmp((const char *)cur_node->name, "path") == 0)
        {
            Path *pathFile = pather(cur_node);
            insertBack(svgFile->paths, pathFile);
        } // deal with groups
        if (strcmp((const char *)cur_node->name, "g") == 0)
        {
            Group *gpFile = grouper(cur_node);
            insertBack(svgFile->groups, gpFile);
        }
    }
    // iterate through attribbutes of the svg struct
    for (xmlAttr *attr = root_element->properties; attr != NULL; attr = attr->next)
    {
        Attribute *store = attribe(attr);
        insertBack(svgFile->otherAttributes, store);
    }

    xmlFreeDoc(doc);
    xmlCleanupParser();
    return svgFile;
}
// function to find and return the extra attributes
Attribute *attribe(xmlAttr *attr)
{
    xmlNode *value = attr->children;
    Attribute *attributes = (Attribute *)malloc(sizeof(Attribute) + strlen((char *)(value->content)) + 1);
    attributes->name = malloc(strlen((char *)attr->name) + 1);
    strcpy(attributes->name, (char *)attr->name);        // store the attribute name
    strcpy(attributes->value, (char *)(value->content)); // store the attribute's value
    return attributes;                                   // return the attributes
}
// function to find and return the attributes of the rectangle
Rectangle *rectangle(xmlNode *cur_node)
{
    Rectangle *rectAtribe = (Rectangle *)malloc(sizeof(Rectangle)); // dynamically allocate the memory
    rectAtribe->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);
    xmlAttr *attr;
    for (attr = cur_node->properties; attr != NULL; attr = attr->next) // iterate through the attributes of a rectangle
    {
        xmlNode *value = attr->children;
        char *valData = (char *)(value->content);

        if (strcmp((char *)attr->name, "x") == 0)
        {
            rectAtribe->x = strtof(valData, &valData);
            strcpy(rectAtribe->units, retrieveData(valData)); // storing the unit
        }
        else if (strcmp((char *)attr->name, "y") == 0)
        {
            rectAtribe->y = strtof(valData, &valData);

            strcpy(rectAtribe->units, retrieveData(valData)); // storing the unit
        }
        else if (strcmp((char *)attr->name, "width") == 0)
        {
            rectAtribe->width = strtof(valData, &valData);
            if (strtof(valData, &valData) >= 0) // proceed if width is +ve
            {

                strcpy(rectAtribe->units, retrieveData(valData)); // storing the unit
            }
            else
            {
                freeList(rectAtribe->otherAttributes);
                return rectAtribe;
            }
        }
        else if (strcmp((char *)attr->name, "height") == 0)
        {
            rectAtribe->height = strtof(valData, &valData);
            if (strtof(valData, &valData) >= 0) // proceed if height is +ve
            {

                strcpy(rectAtribe->units, retrieveData(valData)); // storing the unit
            }
            else
            {
                freeList(rectAtribe->otherAttributes);
                return rectAtribe;
            }
        }
        else
        {
            insertBack(rectAtribe->otherAttributes, attribe(attr));
        }
    }
    return rectAtribe;
}
// function to find and return the attributes of the circle
Circle *circle(xmlNode *cur_node)
{
    Circle *rectAtribe = (Circle *)malloc(sizeof(Circle)); // dynacmically allocate the memory
    rectAtribe->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);
    xmlAttr *attr;
    for (attr = cur_node->properties; attr != NULL; attr = attr->next) // iterate through the attributes of a circle
    {
        xmlNode *value = attr->children;
        char *valData = (char *)(value->content);

        if (strcmp((char *)attr->name, "cx") == 0)
        {
            rectAtribe->cx = strtof(valData, &valData);
            strcpy(rectAtribe->units, retrieveData(valData)); // get the units
        }
        else if (strcmp((char *)attr->name, "cy") == 0)
        {
            rectAtribe->cy = strtof(valData, &valData);
            strcpy(rectAtribe->units, retrieveData(valData)); // get the units
        }
        else if (strcmp((char *)attr->name, "r") == 0)
        {
            rectAtribe->r = strtof(valData, &valData);
            if (strtof(valData, &valData) >= 0) // proceed if radius +ve
            {

                strcpy(rectAtribe->units, retrieveData(valData)); // get the units
            }
            else
            {
                freeList(rectAtribe->otherAttributes);
                return rectAtribe;
            }
        }
        else
        {
            insertBack(rectAtribe->otherAttributes, attribe(attr));
        }
    }
    return rectAtribe;
}
// function to find and store the attributes of the path
Path *pather(xmlNode *cur_node)
{
    Path *rectAtribe = NULL;
    xmlAttr *attr;
    for (attr = cur_node->properties; attr != NULL; attr = attr->next) // iterate through the attributes of a path
    {
        xmlNode *value = attr->children;
        char *valData = (char *)(value->content);
        if (strcmp((char *)attr->name, "d") == 0) // if data is present
        {
            rectAtribe = (Path *)malloc(sizeof(Path) + strlen(valData) + 1);
            rectAtribe->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes); // initialize the list
            strcpy(rectAtribe->data, "");
            strcpy(rectAtribe->data, valData);
        }
    }
    for (attr = cur_node->properties; attr != NULL; attr = attr->next)
    {
        if (strcmp((char *)attr->name, "d") != 0) // if data doesn't present
        {
            insertBack(rectAtribe->otherAttributes, attribe(attr));
        }
    }
    return rectAtribe;
}
// function to find and store the attributes of the group
Group *grouper(xmlNode *cur_node)
{
    Group *rectAtribe = (Group *)malloc(sizeof(Group)); // dynamically allocate the memory
    rectAtribe->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);
    rectAtribe->rectangles = initializeList(rectangleToString, deleteRectangle, compareRectangles);
    rectAtribe->circles = initializeList(circleToString, deleteCircle, compareCircles);
    rectAtribe->paths = initializeList(pathToString, deletePath, comparePaths);
    rectAtribe->groups = initializeList(groupToString, deleteGroup, compareGroups);

    xmlNode *attr;
    xmlAttr *attrReal;
    for (attrReal = cur_node->properties; attrReal != NULL; attrReal = attrReal->next) // iterate through the attribute properties in groups
    {
        insertBack(rectAtribe->otherAttributes, attribe(attrReal));
    }

    for (attr = cur_node->children; attr != NULL; attr = attr->next)
    {
        if (strcmp((const char *)attr->name, "rect") == 0)
        {
            Rectangle *rectFile = rectangle(attr);
            insertBack(rectAtribe->rectangles, rectFile);
        }
        else if (strcmp((const char *)attr->name, "circle") == 0)
        {
            Circle *circFile = circle(attr);
            insertBack(rectAtribe->circles, circFile);
        }
        else if (strcmp((const char *)attr->name, "path") == 0)
        {
            Path *pathFile = pather(attr);
            insertBack(rectAtribe->paths, pathFile);
        }
        else if (strcmp((const char *)attr->name, "g") == 0)
        {
            Group *gpFile = grouper(attr);
            insertBack(rectAtribe->groups, gpFile);
        }
    }
    return rectAtribe;
}
// to find the unit of the measurements
char *retrieveData(char *temp)
{
    int j = 0;
    for (int i = 0; i < strlen(temp); i++)
    {
        if (isalpha(temp[i]) != 0)
        {
            temp[j] = temp[i]; // storing alphabets
            j++;
        }
    }
    temp[j] = '\0';
    return temp;
}
// delete the svg file along with its content
void deleteSVG(SVG *img)
{
    if (img == NULL)
    {
        return;
    }
    clearList(img->otherAttributes);
    clearList(img->circles);
    clearList(img->rectangles);
    clearList(img->paths);
    clearList(img->groups);
    free(img->otherAttributes);
    free(img->rectangles);
    free(img->circles);
    free(img->paths);
    free(img->groups);
    free(img);
}
// store the the string to be printed in a specific format
char *SVGToString(const SVG *img)
{
    char *printAtr = toString(img->otherAttributes);
    char *printRect = toString(img->rectangles);
    char *printCircle = toString(img->circles);
    char *printPath = toString(img->paths);
    char *printGp = toString(img->groups);
    char *info = (char *)malloc(sizeof(char) * (strlen(printGp) + strlen(printAtr) + strlen(printRect) + strlen(printCircle) + strlen(printPath) + strlen(img->namespace) + strlen(img->description) + strlen(img->title) + 109));
    sprintf(info, "namespace: %s\ntitle: %s\ndesc: %s\nAttributes: %s\n----Rectangle---- %s\n----Circles---- %s\n----Paths---- %s\n----Groups---- %s\n", img->namespace, img->title, img->description, printAtr, printRect, printCircle, printPath, printGp); // store the string in specific format
    free(printAtr);
    free(printRect);
    free(printCircle);
    free(printPath);
    free(printGp);
    return info;
}
// just an empty function
void nullFunc() {}
// helper function to iterate through subgroups
void assistGp(Group *gP, List *elements)
{
    void *elem;
    insertBack(elements, (void *)gP);
    ListIterator iter = createIterator(gP->groups);
    while ((elem = nextElement(&iter)) != NULL) // iterate through list
    {
        Group *newGp = (Group *)elem; // typecast
        assistGp(newGp, elements);    // recusrion
    }
}
// to retrieve the list of groups
List *getGroups(const SVG *img)
{
    if (img == NULL)
    {
        return NULL;
    }
    void *elem;
    List *list = initializeList(groupToString, nullFunc, compareGroups);
    ListIterator iter = createIterator(img->groups);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the list
    {
        assistGp((Group *)elem, list);
    }
    return list;
}
// retrieve the list of the groups
List *getRects(const SVG *img)
{
    if (img == NULL)
    {
        return NULL;
    }
    void *elem;
    List *list = initializeList(rectangleToString, nullFunc, compareRectangles);
    ListIterator iter = createIterator(img->rectangles);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the rectangle
    {
        insertBack(list, elem);
    }

    void *new;
    List *tempList = getGroups(img);
    ListIterator newIterator = createIterator(tempList);
    while ((elem = nextElement(&newIterator)) != NULL) // iterate till the end of the group list
    {
        ListIterator latestIterator = createIterator(((Group *)elem)->rectangles);
        while ((new = nextElement(&latestIterator)))
        {
            insertBack(list, new);
        }
    }
    freeList(tempList);
    return list;
}
// retrieve the list of circles
List *getCircles(const SVG *img)
{
    if (img == NULL)
    {
        return NULL;
    }
    void *elem;
    List *list = initializeList(circleToString, nullFunc, compareCircles);
    ListIterator iter = createIterator(img->circles);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the circle list
    {
        insertBack(list, elem);
    }
    void *new;
    List *tempList = getGroups(img);
    ListIterator newIterator = createIterator(tempList);
    while ((elem = nextElement(&newIterator)) != NULL) // iterate till the end of the group list
    {
        ListIterator latestIterator = createIterator(((Group *)elem)->circles);
        while ((new = nextElement(&latestIterator)))
        {
            insertBack(list, new);
        }
    }
    freeList(tempList);
    return list;
}
// retrieve the list of paths
List *getPaths(const SVG *img)
{
    if (img == NULL)
    {
        return NULL;
    }
    void *elem;

    List *list = initializeList(circleToString, nullFunc, compareCircles);
    ListIterator iter = createIterator(img->paths);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the path list
    {
        insertBack(list, elem);
    }
    void *new;
    List *tempList = getGroups(img);
    ListIterator newIterator = createIterator(tempList);
    while ((elem = nextElement(&newIterator)) != NULL) // iterate till the end of the group list
    {
        ListIterator latestIterator = createIterator(((Group *)elem)->paths);
        while ((new = nextElement(&latestIterator)))
        {
            insertBack(list, new);
        }
    }
    freeList(tempList);
    return list;
}
// retrieve the numeber of rectangle with the given area
int numRectsWithArea(const SVG *img, float area)
{
    if (img == NULL)
    {
        return 0;
    }
    int increment = 0;
    void *elem;
    List *tempList = getRects(img);
    ListIterator iter = createIterator(tempList);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the rect list
    {
        Rectangle *typecast = (Rectangle *)elem;
        float calculatedArea = (typecast->width) * (typecast->height); // area calculated
        calculatedArea = ceil(calculatedArea);
        if (calculatedArea == area)
        {
            increment++;
        }
    }
    freeList(tempList); // free the list
    return increment;
}
// Function that returns the number of all circles with the specified area
int numCirclesWithArea(const SVG *img, float area)
{
    if (img == NULL)
    {
        return 0;
    }
    int increment = 0;
    void *elem;
    List *tempList = getCircles(img);
    ListIterator iter = createIterator(tempList);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the circle list
    {
        Circle *typecast = (Circle *)elem;
        float calculatedArea = 3.1415 * (typecast->r) * (typecast->r); // calcute the circle area
        calculatedArea = ceil(calculatedArea);
        if (calculatedArea == ceil(area))
        {
            increment++;
        }
    }
    freeList(tempList); // free the list
    return increment;
}
// Function that returns the number of all paths with the specified data - i.e. Path.data field
int numPathsWithdata(const SVG *img, const char *data)
{
    if (img == NULL)
    {
        return 0;
    }
    int increment = 0;
    void *elem;
    List *tempList = getPaths(img);
    ListIterator iter = createIterator(tempList);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the path list
    {
        Path *typecast = (Path *)elem;

        if (strcmp(typecast->data, data) == 0) // match of data found
        {
            increment++;
        }
    }
    freeList(tempList); // free the list
    return increment;
}
// Function that returns the number of all groups with the specified length - see A1 Module 2 for details
int numGroupsWithLen(const SVG *img, int len)
{
    if (img == NULL)
    {
        return 0;
    }
    int increment = 0;
    int total = 0;
    void *elem;
    List *tempList = getGroups(img);
    ListIterator iter = createIterator(tempList);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the group list
    {
        Group *typecast = (Group *)elem;
        total = typecast->groups->length + typecast->circles->length + typecast->rectangles->length + typecast->paths->length;
        if (total == len)
        {
            increment++;
        }
    }
    freeList(tempList); // free the list
    return increment;
}
// Function that returns the total number of Attribute structs in the SVG struct
int numAttr(const SVG *img)
{
    if (img == NULL)
    {
        return 0;
    }

    int inc = 0;
    int inc2 = 0;
    int inc3 = 0;
    int inc4 = 0;
    int total = 0;
    int svgCount = img->otherAttributes->length;
    void *elem;
    List *tempList1 = getGroups(img);
    List *tempList2 = getRects(img);
    List *tempList3 = getCircles(img);
    List *tempList4 = getPaths(img);

    ListIterator iter = createIterator(tempList1);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the group list
    {
        Group *typecast1 = (Group *)elem;
        inc += typecast1->otherAttributes->length;
    }

    ListIterator iter2 = createIterator(tempList2);
    while ((elem = nextElement(&iter2)) != NULL) // iterate till the end of the rectangle list
    {
        Rectangle *typecast2 = (Rectangle *)elem;
        inc2 += typecast2->otherAttributes->length;
    }

    ListIterator iter3 = createIterator(tempList3);
    while ((elem = nextElement(&iter3)) != NULL) // iterate till the end of the circle list
    {
        Circle *typecast3 = (Circle *)elem;
        inc3 += typecast3->otherAttributes->length;
    }

    ListIterator iter4 = createIterator(tempList4);
    while ((elem = nextElement(&iter4)) != NULL) // iterate till the end of the path list
    {
        Path *typecast4 = (Path *)elem;
        inc4 += typecast4->otherAttributes->length;
    }

    total = svgCount + inc + inc2 + inc3 + inc4;
    // free all the lists
    freeList(tempList1);
    freeList(tempList2);
    freeList(tempList3);
    freeList(tempList4);
    return total;
}

// Assignment 2


//Helper function to check the validity of xml file will xsd file i.e. check the format
int checkHelper(xmlDoc* file,const char* xsd ){
    //check if file and xsd are not NULL
    if (file == NULL||xsd == NULL){
        return 0;
    }
    xmlSchemaPtr schema = NULL;
    xmlSchemaParserCtxtPtr ctxt;

    ctxt = xmlSchemaNewParserCtxt(xsd);
    if(ctxt == NULL){
        //if schema parsed is NULL
        return 0;
    }

    schema = xmlSchemaParse(ctxt);
    xmlSchemaFreeParserCtxt(ctxt);

    if(schema == NULL)
    {
        //if schema is NULL
        return 0;
    }

    xmlSchemaValidCtxtPtr ctxt2;
    int ret;

    ctxt2 = xmlSchemaNewValidCtxt(schema);
    if (ctxt2 == NULL)
    {
        xmlSchemaFree(schema);
        xmlSchemaCleanupTypes();
        return 0;
    }
    ret = xmlSchemaValidateDoc(ctxt2, file);
    xmlSchemaFree(schema);
    xmlSchemaFreeValidCtxt(ctxt2);
    xmlSchemaCleanupTypes();

    if (ret != 0)
    {
        return 0;
    }
    return 1;
}

SVG *createValidSVG(const char *fileName, const char *schemaFile)
{ // if file doesn't exist, return NULL
    if (fileName == NULL)
    {
        return NULL;
    }
    xmlDoc *doc = NULL;
    xmlNode *root_element = NULL;

    LIBXML_TEST_VERSION
    //dynamically allocated memory
    SVG *svgFile = (SVG *)malloc(sizeof(SVG));
    doc = xmlReadFile(fileName, NULL, 0);
    // if failed to parse, return NULL
    if (doc == NULL)
    {
        return NULL;
    }

    int returnCheck = checkHelper(doc, schemaFile);
    if (returnCheck == 0)
    {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return NULL;
    }
    
    root_element = xmlDocGetRootElement(doc); // point to root node
    svgFile->otherAttributes = initializeList(attributeToString, deleteAttribute, compareAttributes);
    svgFile->rectangles = initializeList(rectangleToString, deleteRectangle, compareRectangles);
    svgFile->circles = initializeList(circleToString, deleteCircle, compareCircles);
    svgFile->paths = initializeList(pathToString, deletePath, comparePaths);
    svgFile->groups = initializeList(groupToString, deleteGroup, compareGroups);
    strcpy(svgFile->namespace, "");
    strcpy(svgFile->description, "");
    strcpy(svgFile->title, "");
    strcpy(svgFile->namespace, (char *)root_element->ns->href);
    titleDesc(root_element->children, svgFile);
    // iterate through all nodes
    for (xmlNode *cur_node = root_element->children; cur_node != NULL; cur_node = cur_node->next)
    { // deal with rectnagles
        if (strcmp((const char *)cur_node->name, "rect") == 0)
        {
            Rectangle *rectFile = rectangle(cur_node);
            insertBack(svgFile->rectangles, rectFile);
        } // deal with circles
        if (strcmp((const char *)cur_node->name, "circle") == 0)
        {
            Circle *circFile = circle(cur_node);
            insertBack(svgFile->circles, circFile);
        } // deal with paths
        if (strcmp((const char *)cur_node->name, "path") == 0)
        {
            Path *pathFile = pather(cur_node);
            insertBack(svgFile->paths, pathFile);
        } // deal with groups
        if (strcmp((const char *)cur_node->name, "g") == 0)
        {
            Group *gpFile = grouper(cur_node);
            insertBack(svgFile->groups, gpFile);
        }
    }
    // iterate through attribbutes of the svg struct
    for (xmlAttr *attr = root_element->properties; attr != NULL; attr = attr->next)
    {
        Attribute *store = attribe(attr);
        insertBack(svgFile->otherAttributes, store);
    }

    xmlFreeDoc(doc);    //free the doc
    xmlCleanupParser();
    return svgFile;
}

//function to add title and description to tree
void titleDescTree(xmlNodePtr root, const SVG* svg){
    
    if(strcmp(svg->description,"") != 0){
        xmlNewTextChild(root, NULL,(const xmlChar*)"title", (const xmlChar*)svg->title);
    }
    if(strcmp(svg->title,"") != 0){
        xmlNewTextChild(root, NULL,(const xmlChar*)"desc", (const xmlChar*)svg->description);
    }
}

xmlDoc * svgToTree(const SVG * img){

    xmlDocPtr doc = NULL;       /* document pointer */
    xmlNodePtr root_node = NULL;/* node pointers */ 
    /* 
     * Creates a new document, a node and set it as a root node
     */
    doc = xmlNewDoc((const xmlChar*)"1.0");
    root_node = xmlNewNode(NULL, (const xmlChar*)"svg");
    xmlDocSetRootElement(doc, root_node);
    if (root_node != NULL){
        xmlNsPtr ns = xmlNewNs(root_node,(xmlChar *)img->namespace,NULL);
        xmlSetNs(root_node,ns);
        titleDescTree(root_node,img);
        attTree(root_node, img->otherAttributes);
        //declared the lists
        List* rects = img->rectangles;
        List* circles = img->circles;
        List* grps = img->groups;
        List* paths = img->paths;
        //helper function for adding rectangle, circle, path to tree
        RCPTree(root_node, rects, circles, paths);
        //helper function for adding group to tree
        groupTree(root_node, grps);
    }
    return doc;
}

//helper function to add attributes to tree
void attTree(xmlNodePtr root_node, List* tempList){
    void *elem;
    if (tempList == NULL || root_node == NULL)
    {   //if list or the node(root node is NULL)
        return;
    }
    //declared iterator
    ListIterator iter = createIterator(tempList);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the group list
    {
        Attribute *typecast = (Attribute *)elem;    //typecasting to Attribute
        xmlNewProp(root_node, (const xmlChar*)typecast->name, (const xmlChar*)typecast->value); //for adding property
    }
}

//helper function for adding rectangle, circle, path to tree
void RCPTree(xmlNodePtr root_node, List* rects, List* circles, List * paths){

    void *elem;
    if (rects != NULL){ //if rectangle list is not NULL
        //declared the iterator
        ListIterator iter = createIterator(rects);
        while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the rectangle list
        {
            Rectangle *typecast = (Rectangle *)elem;    //typecasting
            xmlNodePtr rectNode = xmlNewChild(root_node, NULL, (const xmlChar*)"rect", NULL);
            char* store = (char*)malloc(sizeof(char)*999999);   //dynamic allocation
            
            //adding properties of each rectangles in the specified format
            sprintf(store, "%f%s", typecast->x, typecast->units);
            xmlNewProp(rectNode, (const xmlChar*)"x", (const xmlChar*)store);

            sprintf(store, "%f%s", typecast->y, typecast->units);
            xmlNewProp(rectNode, (const xmlChar*)"y", (const xmlChar*)store);

            sprintf(store, "%f%s", typecast->width, typecast->units);
            xmlNewProp(rectNode, (const xmlChar*)"width", (const xmlChar*)store);

            sprintf(store, "%f%s", typecast->height, typecast->units);
            xmlNewProp(rectNode, (const xmlChar*)"height", (const xmlChar*)store);

            attTree(rectNode, typecast->otherAttributes);

            free(store);//free the dynamically allocated memory
        }
    }

    if (circles != NULL){//if the circle is not NULL
        //declared the iterator
        ListIterator iter = createIterator(circles);
        while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the circle list
        {
            Circle *typecast = (Circle *)elem;  //typecasting
            xmlNodePtr rectNode = xmlNewChild(root_node, NULL, (const xmlChar*)"circle", NULL);
            char* store = (char*)malloc(sizeof(char)*999999);   //dynacmic allocation
            
            //adding properties of each circles in the specified format
            sprintf(store, "%f%s", typecast->cx, typecast->units);
            xmlNewProp(rectNode, (const xmlChar*)"cx", (const xmlChar*)store);

            sprintf(store, "%f%s", typecast->cy, typecast->units);
            xmlNewProp(rectNode, (const xmlChar*)"cy", (const xmlChar*)store);

            sprintf(store, "%f%s", typecast->r, typecast->units);
            xmlNewProp(rectNode, (const xmlChar*)"r", (const xmlChar*)store);

            attTree(rectNode, typecast->otherAttributes);

            free(store);    //free the dynamically allocated memory
        }
    }

    if (paths != NULL){//if the path is not NULL
        //declared the iterator
        ListIterator iter = createIterator(paths);
        while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the group list
        {
            Path *typecast = (Path *)elem; //typecasting
            xmlNodePtr rectNode = xmlNewChild(root_node, NULL, (const xmlChar*)"path", NULL);   //add the child
            //add the attributes or properties
            xmlNewProp(rectNode, (const xmlChar*)"d", (const xmlChar*)typecast->data);
            attTree(rectNode, typecast->otherAttributes);
        }
    }
}
//helper function for adding group to tree
void groupTree(xmlNodePtr root_node, List *grps){

    if (grps == NULL){//if group list is null
        return;
    }
    void*elem;
    //declared the iteator
    ListIterator iter = createIterator(grps);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the group list
    {
        Group *typecast = (Group *)elem; //typecasting
        xmlNodePtr rectNode = xmlNewChild(root_node, NULL, (const xmlChar*)"g", NULL);
        RCPTree(rectNode, typecast->rectangles, typecast->circles, typecast->paths);
        attTree(rectNode, typecast->otherAttributes);
        groupTree(rectNode, typecast->groups);
    }
}

bool validateSVG(const SVG* img, const char* schemaFile){
    if (img == NULL || schemaFile == NULL){
        //if svg and schemafile is NULL
        return false;
    }
    xmlDocPtr doc = svgToTree(img);
    if(checkHelper(doc, schemaFile) != 1){
        //free the memory
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return false;
    }
    if(img->circles == NULL || img->rectangles == NULL || img->paths == NULL || img->groups == NULL || img->otherAttributes == NULL || validHelp(img) == 0){
        return false;
    }
    //free the memory
    xmlFreeDoc(doc);
    xmlCleanupParser();
    return true;
}

int validHelp(const SVG* img){
    void *elem;
    if (getRects(img) != NULL){//if rectangle list not NULL
        ListIterator iter = createIterator(getRects(img));
        while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the group list
        {
            Rectangle *typecast = (Rectangle *)elem;    //typecast
            //error check
            if (typecast->height < 0 || typecast->width < 0 || typecast->otherAttributes == NULL || validAtr(typecast->otherAttributes) == 0){
                return 0;
            }
        }
    }

    if (getCircles(img) != NULL){//if circle list is not NULL
        ListIterator iter = createIterator(getCircles(img));
        while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the group list
        {
            Circle *typecast = (Circle *)elem; //typecast
            //error check
            if (typecast->r < 0 || typecast->otherAttributes == NULL || validAtr(typecast->otherAttributes) == 0){
                return 0;
            }
        }
    }

    if (getPaths(img) != NULL){//if p[ath list is not null]
        ListIterator iter = createIterator(getPaths(img));
        while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the group list
        {
            Path *typecast = (Path *)elem;//typecast
            //error check
            if (typecast->data == NULL || typecast->otherAttributes == NULL || validAtr(typecast->otherAttributes) == 0){
                return 0;
            }
        }
    }

    if (getGroups(img) != NULL){//if group list is not null
        ListIterator iter = createIterator(getGroups(img));
        while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the group list
        {
            Group *typecast = (Group *)elem; //typecast
            //error check
            if (typecast->rectangles == NULL || typecast->circles == NULL || typecast->paths == NULL || typecast->groups == NULL || typecast->otherAttributes == NULL || validAtr(typecast->otherAttributes) == 0){
                return 0;
            }
        }
    }
    return 1;
}

//Helper function to check if the name of any attribute is not null
int validAtr(List* list){
    void *elem;
    ListIterator iter = createIterator(list);
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the group list
    {
        Attribute *typecast = (Attribute *)elem;//typecasting
        if (typecast->name== NULL){
            return 0;
        }
    }
    return 1;
}
//writing to the new file
bool writeSVG(const SVG* img, const char* fileName){
    if (img == NULL || fileName == NULL){
        return false;
    }
    xmlDocPtr doc = svgToTree(img);
    if (doc == NULL)
    {
        return false;
    }
    xmlSaveFormatFileEnc(fileName, doc, "UTF-8", 1);
    if(xmlSaveFormatFileEnc(fileName, doc, "UTF-8", 1) == -1){
        xmlFreeDoc(doc);
        xmlCleanupParser();
        return false;
    }
    //free the memory
    xmlFreeDoc(doc);
    xmlCleanupParser();
    
    return true;
}

void update(Attribute* newAttribute, List* list){
    void*elem;
    ListIterator iter = createIterator(list);
    
    while ((elem = nextElement(&iter)) != NULL) // iterate till the end of the list
    {
        Attribute *typecast = (Attribute *)elem;
        if(strcmp(newAttribute->name, typecast->name)==0)   //if string matched, copy the value
        {
            strcpy(typecast->value, newAttribute->value);
            free(newAttribute->name);
            free(newAttribute);
            return;
        }
    }
        insertBack(list, newAttribute);
}

/** Function to setting an attribute in an SVG or component **/
bool setAttribute(SVG* img, elementType elemType, int elemIndex, Attribute* newAttribute){
    //Error checking
    if (img == NULL || newAttribute == NULL || (elemIndex < 0 &&  elemType != SVG_IMG))
    {
        return false;
    }
    //for svg
    if (elemType == SVG_IMG)
    {
        update(newAttribute, img->otherAttributes);
        return true;
    }
    //for rectangle
    else if (elemType == RECT){
        int increment = 0;
        void *elem;
        List *tempList = img->rectangles;
        //create iterator
        ListIterator iter = createIterator(tempList);
        while (increment <= elemIndex) // iterate till the given index
        {
            elem = nextElement(&iter);
            //check if element is NULL
            if (elem == NULL) {
                free(newAttribute->name);
                free(newAttribute);
                return false;  
            }
            increment++;
        }
        Rectangle *typecast = (Rectangle *)elem;

        if (strcmp(newAttribute->name, "x") == 0){
            typecast->x = atof(newAttribute->value);
            free(newAttribute->name);
            free(newAttribute);
            return true;
        }
        else if (strcmp(newAttribute->name, "y") == 0)
        {
            typecast->y = atof(newAttribute->value);
            free(newAttribute->name);
            free(newAttribute);
            return true;
        }
        else if(strcmp(newAttribute->name, "width") == 0){
            typecast->width = atof(newAttribute->value);
            free(newAttribute->name);
            free(newAttribute);
            return true;
        }
        else if(strcmp(newAttribute->name, "height") == 0){
            typecast->height = atof(newAttribute->value);
            free(newAttribute->name);
            free(newAttribute);
            return true;
        }
        else
        {
            update(newAttribute, typecast->otherAttributes);
            return true;
        }
    }
    //for circles
    else if (elemType == CIRC){
        int increment = 0;
        void *elem;
        List *tempList = img->circles;
        ListIterator iter = createIterator(tempList);
        while (increment <= elemIndex) // iterate till the given index
        {
            elem = nextElement(&iter);
            if (elem == NULL) 
            {
                free(newAttribute->name);
                free(newAttribute);
                return false;  
            }
            increment++;
        }
        Circle *typecast = (Circle *)elem;

        if (strcmp(newAttribute->name, "cx") == 0){
            typecast->cx = atof(newAttribute->value);
            free(newAttribute->name);
            free(newAttribute);
            return true;
        }
        else if (strcmp(newAttribute->name, "cy") == 0)
        {
            typecast->cy = atof(newAttribute->value);
            free(newAttribute->name);
            free(newAttribute);
            return true;
        }
        else if(strcmp(newAttribute->name, "r") == 0){
            typecast->r = atof(newAttribute->value);
            free(newAttribute->name);
            free(newAttribute);
            return true;
        }
        else
        {
            update(newAttribute, typecast->otherAttributes);
            return true;
        }
    }
    //for paths
    else if (elemType == PATH){
        int increment = 0;
        void *elem;
        List *tempList = img->paths;
        ListIterator iter = createIterator(tempList);
        while (increment <= elemIndex) // iterate till the given index
        {
            elem = nextElement(&iter);
            if (elem == NULL) {
                free(newAttribute->name);
                free(newAttribute);
                return false;  
            }
            increment++;
        }
        Path *typecast = (Path *)elem;//typecasting

        if (strcmp(newAttribute->name, "d") == 0){
            strcpy(typecast->data,newAttribute->value);
            free(newAttribute->name);
            free(newAttribute);
            return true;
        }
        else
        {
            update(newAttribute, typecast->otherAttributes);
            return true;
        }
    }
    //for groups
    else if (elemType == GROUP){
        int increment = 0;
        void *elem;
        List *tempList = img->groups;
        ListIterator iter = createIterator(tempList);
        while (increment <= elemIndex) // iterate till the given index
        {
            elem = nextElement(&iter);
            if (elem == NULL){
                free(newAttribute->name);
                free(newAttribute);
                return false;  
            }
            increment++;
        }
        Group *typecast = (Group *)elem;
        update(newAttribute, typecast->otherAttributes);
        return true;
    }
    else{
        free(newAttribute->name);
        free(newAttribute);
        return false;
    }
    return true;
}

/** Function to adding an element - Circle, Rectngle, or Path - to an SVG **/
void addComponent(SVG* img, elementType type, void* newElement){
    if(img == NULL || newElement == NULL)
    {   //error check
        return;
    }
    if (type == RECT)
    {
        insertBack(img->rectangles, newElement);
    }
    else if (type == CIRC)
    {
        insertBack(img->circles, newElement);
    }
    else if (type == PATH)
    {
        insertBack(img->paths, newElement);
    }
}

//Modeule 3

/** Function to converting an Attribute into a JSON string**/
char* attrToJSON(const Attribute *a)
{
    char* store;
    if (a == NULL){ //if attribute list is null
        store = (char*)malloc(sizeof(char) * 4);
        sprintf(store, "{}");
        return store;
    }
    store = (char*)malloc(sizeof(char) * (strlen(a->name) + strlen(a->value) + 28));
    sprintf(store, "{\"name\":\"%s\",\"value\":\"%s\"}", a->name,a->value);
    return store;
}

/** Function to converting a Circle into a JSON string**/
char* circleToJSON(const Circle *c)
{
    char *store;
    if (c == NULL) {//if circle list is NULL
        store  = (char *)malloc(sizeof(char) * 4);
        strcpy(store,"{}");
        return store;
    }
    int numElem = c->otherAttributes->length;
    store =(char *) malloc(sizeof(char) * (strlen(c->units) + 138));
    //stored in specified format
    sprintf(store,"{\"cx\":%.2f,\"cy\":%.2f,\"r\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}",c->cx,c->cy,c->r,numElem,c->units);

    return store;
}

char* rectToJSON(const Rectangle *r){
    char *store;
    if (r == NULL) {//if rectangle list is NULL
        store  = (char *)malloc(sizeof(char) * 4);
        strcpy(store,"{}");
        return store;
    }
    int numElem = r->otherAttributes->length;
    store =(char *) malloc(sizeof(char) * (strlen(r->units) + 145));
    //stored in specified format
    sprintf(store,"{\"x\":%.2f,\"y\":%.2f,\"w\":%.2f,\"h\":%.2f,\"numAttr\":%d,\"units\":\"%s\"}",r->x,r->y,r->width,r->height,numElem,r->units);
    return store;
}

char* pathToJSON(const Path *p){
    char *store;
    if (p == NULL) {//if path List is NULL
        store  = (char *)malloc(sizeof(char) * 4);
        strcpy(store,"{}");
        return store;
    }
    int numElem = p->otherAttributes->length;
    store =(char *) malloc(sizeof(char) * (strlen(p->data) + 41));
    char dat[strlen(p->data)];
    //if length exceeds 64
    strcpy(dat, p->data);
    dat[64] = '\0';
    
    sprintf(store,"{\"d\":\"%s\",\"numAttr\":%d}",dat,numElem);

    return store;
}

char* groupToJSON(const Group *g){

    char *store;
    if (g == NULL) {//if group list is NULL
        store  = (char *)malloc(sizeof(char) * 4);
        strcpy(store,"{}");
        return store;
    }
    int numChild =  g->circles->length + g->groups->length + g->paths->length + g->rectangles->length;
    int numElem = g->otherAttributes->length;
    store = (char *) malloc(sizeof(char) * 66);
    //stored in specified format
    sprintf(store,"{\"children\":%d,\"numAttr\":%d}",numChild,numElem);
    return store;
}
char* SVGtoJSON(const SVG* img){
    char *store;
    if (img == NULL) {//if img is NULL
        //memory allocation
        store  = (char *)malloc(sizeof(char) * 4);
        strcpy(store,"{}");
        return store;
    }
    store = (char *)malloc(sizeof(char) * (130));
    //declared lists
    List * rect  = getRects(img);
    List * circ  = getCircles(img);
    List * path  = getPaths(img);
    List * grp  = getGroups(img);
    
    int numR = rect->length;
    int numC = circ->length;
    int numP = path->length;
    int numG = grp->length;   
    //stored in specified format
    sprintf(store,"{\"numRect\":%d,\"numCirc\":%d,\"numPaths\":%d,\"numGroups\":%d}",numR, numC, numP, numG);
    //free the lists
    freeList(rect);
    freeList(circ);
    freeList(path);
    freeList(grp);

    return store;
}

/** Function to converting a list of Attribute structs into a JSON string**/
char* attrListToJSON(const List *list){
    
    if (list == NULL){
        char* store = malloc(sizeof(char)*4);
        strcpy(store, "[]");
        return store;
    }
    //create iteraotor
    ListIterator iter = createIterator((List*)list);
	char* str;
	//memory allocation
	str = (char*)malloc(sizeof(char)*3);
	strcpy(str, "[");
	
	void* elem;
	while((elem = nextElement(&iter)) != NULL){
        Attribute* atr = (Attribute*) elem;//typecasting
		char* currDescr = attrToJSON(atr);
		int newLen = strlen(str)+50+strlen(currDescr);
		str = (char*)realloc(str, newLen);
        
        if (strcmp(str, "[") != 0) {
            strcat(str, ",");
        }
		strcat(str, currDescr);
		free(currDescr);
	}
     strcat(str,"]");
	
	return str;
}

/** Function to converting a list of Circle structs into a JSON string**/
char* circListToJSON(const List *list){
    if (list == NULL){
        char* store = malloc(sizeof(char)*4);
        strcpy(store, "[]");
        return store;
    }
    //create iterator
    ListIterator iter = createIterator((List*)list);
	char* str;
		
	str = (char*)malloc(sizeof(char)*3);
	strcpy(str, "[");
	
	void* elem;
	while((elem = nextElement(&iter)) != NULL){
        Circle* atr = (Circle*) elem;//typecasting
		char* currDescr = circleToJSON(atr);
		int newLen = strlen(str)+50+strlen(currDescr);
		str = (char*)realloc(str, newLen); //realloction memory
        
        if (strcmp(str, "[") != 0) {
            strcat(str, ",");
        }
		strcat(str, currDescr);
		free(currDescr);
	}
     strcat(str,"]");
	
	return str;
}

/** Function to converting a list of Rectangle structs into a JSON string**/
char* rectListToJSON(const List *list){
    if (list == NULL){
        char* store = malloc(sizeof(char)*4);
        strcpy(store, "[]");
        return store;
    }
    //create iterator
    ListIterator iter = createIterator((List* )list);
	char* str;
		
	str = (char*)malloc(sizeof(char)*3);
	strcpy(str, "[");
	
	void* elem;
	while((elem = nextElement(&iter)) != NULL){
        Rectangle* atr = (Rectangle*) elem; //typecasting
		char* currDescr = rectToJSON(atr);
		int newLen = strlen(str)+50+strlen(currDescr);
		str = (char*)realloc(str, newLen);
        
        if (strcmp(str, "[") != 0) {
            strcat(str, ",");
        }
		strcat(str, currDescr);
		free(currDescr);
	}
     strcat(str,"]");
	
	return str;
}

/** Function to converting a list of Path structs into a JSON string*/
char* pathListToJSON(const List *list){
    if (list == NULL){
        //when lis is NULL
        char* store = malloc(sizeof(char)*4);
        strcpy(store, "[]");
        return store;
    }
        //create iterator
    ListIterator iter = createIterator((List*)list);
	char* str;
		//memory allocation
	str = (char*)malloc(sizeof(char)*3);
	strcpy(str, "[");
	
	void* elem;
	while((elem = nextElement(&iter)) != NULL){
        Path* atr = (Path*) elem;
		char* currDescr = pathToJSON(atr);
		int newLen = strlen(str)+50+strlen(currDescr);
		str = (char*)realloc(str, newLen);
        
        if (strcmp(str, "[") != 0) {
            strcat(str, ",");
        }
		strcat(str, currDescr);
		free(currDescr);
	}
     strcat(str,"]");
	
	return str;
}

/** Function to converting a list of Group structs into a JSON string**/
char* groupListToJSON(const List *list){
    if (list == NULL){
        //when list is NULL
        char* store = malloc(sizeof(char)*4);
        strcpy(store, "[]");
        return store;
    }
    //create Iterator
    ListIterator iter = createIterator((List*)list);
	char* str;
		
	str = (char*)malloc(sizeof(char)*3); //dynamic allocation
	strcpy(str, "[");
	
	void* elem;
	while((elem = nextElement(&iter)) != NULL){
        Group* atr = (Group*) elem;//typecasting
		char* currDescr = groupToJSON(atr);
		int newLen = strlen(str)+50+strlen(currDescr);
		str = (char*)realloc(str, newLen);  //memory reallocation
        
        if (strcmp(str, "[") != 0) {
            strcat(str, ",");
        }
		strcat(str, currDescr);
		free(currDescr);
	}
     strcat(str,"]");
	
	return str;
}
