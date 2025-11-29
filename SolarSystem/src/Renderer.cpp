// ============================================================================
// ملف Renderer.cpp - تنفيذ كلاس الراسم
// ============================================================================
// هذا الملف يحتوي على جميع الدوال التي تنفذ رسم المشهد
// يتضمن تهيئة OpenGL ورسم النظام الشمسي وواجهة المستخدم
// ============================================================================

// تضمين ملف تعريف كلاس الراسم
#include "../include/Renderer.h"

// تضمين مكتبة OpenGL للرسومات ثلاثية الأبعاد
#include <GL/glut.h>

// تضمين مكتبة الرياضيات للدوال الرياضية
#include <math.h>

// تضمين مكتبة الإدخال/الإخراج القياسية (للطباعة)
#include <stdio.h>

// ============================================================================
// ثوابت رياضية
// ============================================================================

// ثابت رياضي لقيمة π (باي) بدقة عالية
const float M_PI_CONST = 3.14159265358979323846f;

// ============================================================================
// دالة البناء Constructor - تقوم بإنشاء راسم جديد
// ============================================================================
// هذه الدالة تستدعى عند إنشاء كائن Renderer
// تقوم بحفظ المؤشرات إلى المكونات الأساسية
// ============================================================================
Renderer::Renderer(StarField* sf, SolarSystem* ss, Camera* cam) 
    // قائمة التهيئة: تهيئة المتغيرات مباشرة قبل دخول جسم الدالة
    : starField(sf),      // حفظ مؤشر إلى حقل النجوم
      solarSystem(ss),    // حفظ مؤشر إلى النظام الشمسي
      camera(cam)         // حفظ مؤشر إلى الكاميرا
{}

// ============================================================================
// دالة تهيئة OpenGL - إعداد إعدادات OpenGL الأساسية
// ============================================================================
// هذه الدالة تستدعى مرة واحدة عند بدء التطبيق
// تقوم بإعداد جميع إعدادات OpenGL (الإضاءة، الألوان، إلخ)
// ============================================================================
void Renderer::initGL() {
    // تفعيل اختبار العمق (Depth Test)
    // يضمن رسم الأجسام القريبة فوق الأجسام البعيدة
    glEnable(GL_DEPTH_TEST);
    
    // تفعيل الإضاءة (Lighting)
    // يسمح بتطبيق تأثيرات الإضاءة على الأجسام
    glEnable(GL_LIGHTING);
    
    // تفعيل مصدر الإضاءة رقم 0 (Light 0)
    glEnable(GL_LIGHT0);
    
    // تفعيل مادة الألوان (Color Material)
    // يسمح بتغيير لون الأجسام مباشرة
    glEnable(GL_COLOR_MATERIAL);
    
    // تحديد كيفية تطبيق الألوان على المواد
    // GL_FRONT: تطبيق على الوجه الأمامي فقط
    // GL_AMBIENT_AND_DIFFUSE: تطبيق على الإضاءة المحيطة والمنتشرة
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
    
    // تحديد نموذج التظليل (Shading Model)
    // GL_SMOOTH: تظليل ناعم (Gouraud Shading)
    glShadeModel(GL_SMOOTH);
    
    // ========================================================================
    // إعداد مصدر الإضاءة (Light Source)
    // ========================================================================
    
    // موضع مصدر الإضاءة (في المركز - حيث توجد الشمس)
    GLfloat lightPos[] = {0.0f, 0.0f, 0.0f, 1.0f};
    
    // الإضاءة المحيطة (Ambient Light) - إضاءة عامة خفيفة
    // RGB: (0.15, 0.15, 0.15) = رمادي داكن
    GLfloat lightAmbient[] = {0.15f, 0.15f, 0.15f, 1.0f};
    
    // الإضاءة المنتشرة (Diffuse Light) - الإضاءة المباشرة
    // RGB: (1.0, 0.95, 0.8) = أصفر فاتح (لون الشمس)
    GLfloat lightDiffuse[] = {1.0f, 0.95f, 0.8f, 1.0f};
    
    // الإضاءة المرآتية (Specular Light) - اللمعان
    // RGB: (1.0, 1.0, 0.9) = أبيض مصفر
    GLfloat lightSpecular[] = {1.0f, 1.0f, 0.9f, 1.0f};
    
    // تطبيق إعدادات الإضاءة على Light 0
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);      // موضع الإضاءة
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);    // الإضاءة المحيطة
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);    // الإضاءة المنتشرة
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular); // الإضاءة المرآتية
    
    // إعداد التوهين (Attenuation) - كيف تضعف الإضاءة مع المسافة
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);   // التوهين الثابت (1.0 = لا توهين)
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0f);    // التوهين الخطي (0.0 = لا توهين خطي)
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);  // التوهين التربيعي (0.0 = لا توهين تربيعي)
    
    // ========================================================================
    // إعداد خصائص المواد (Material Properties)
    // ========================================================================
    
    // الإضاءة المرآتية للمواد (Specular Reflection)
    // RGB: (0.6, 0.6, 0.6) = رمادي فاتح
    GLfloat matSpecular[] = {0.6f, 0.6f, 0.6f, 1.0f};
    
    // اللمعان (Shininess) - مدى حدة اللمعان
    // 60.0 = لمعان متوسط
    GLfloat matShininess[] = {60.0f};
    
    // تطبيق خصائص المواد
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);    // الإضاءة المرآتية
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);  // اللمعان
    
    // تعيين لون الخلفية (Background Color)
    // RGB: (0.0, 0.0, 0.02) = أزرق داكن جداً (لون الفضاء)
    glClearColor(0.0f, 0.0f, 0.02f, 1.0f);
}

// ============================================================================
// دالة رسم المحاكاة - رسم النظام الشمسي الكامل
// ============================================================================
// هذه الدالة تستدعى في كل إطار لرسم المشهد الحالي
// ============================================================================
void Renderer::renderSimulation() {
    // مسح المخازن المؤقتة (Buffer Clearing)
    // GL_COLOR_BUFFER_BIT: مسح مخزن الألوان
    // GL_DEPTH_BUFFER_BIT: مسح مخزن العمق
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    // تحميل مصفوفة الوحدة (إعادة تعيين التحويلات)
    glLoadIdentity();
    
    // متغيرات لتخزين موضع الكاميرا ونقطة النظر
    float camX, camY, camZ, lookX, lookY, lookZ;
    
    // الحصول على موضع الكاميرا ونقطة النظر من الكاميرا
    getCameraPosition(camX, camY, camZ, lookX, lookY, lookZ);
    
    // تعيين موضع الكاميرا ونقطة النظر
    // gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
    //   eye: موضع الكاميرا
    //   center: نقطة النظر (أين تنظر الكاميرا)
    //   up: اتجاه الأعلى (0, 1, 0) = المحور Y
    gluLookAt(camX, camY, camZ, lookX, lookY, lookZ, 0.0f, 1.0f, 0.0f);
    
    // رسم حقل النجوم (الخلفية النجمية)
    starField->draw(solarSystem->getTime());
    
    // رسم النظام الشمسي (الشمس والكواكب)
    solarSystem->draw();
    
    // رسم واجهة المستخدم (HUD - Head-Up Display)
    renderHUD();
    
    // تبديل المخازن المؤقتة (Double Buffering)
    // يعرض الإطار المرسوم ويجهز الإطار التالي للرسم
    glutSwapBuffers();
}

// ============================================================================
// دالة الحصول على موضع الكاميرا - حساب موضع الكاميرا بناءً على الإعدادات
// ============================================================================
// هذه الدالة تحسب موضع الكاميرا ونقطة النظر بناءً على إعدادات الكاميرا
// camX, camY, camZ: موضع الكاميرا (يتم ملؤها)
// lookX, lookY, lookZ: نقطة النظر (يتم ملؤها)
// ============================================================================
void Renderer::getCameraPosition(float& camX, float& camY, float& camZ, 
                      float& lookX, float& lookY, float& lookZ) {
    // الحصول على الكوكب المُركز عليه من الكاميرا
    int focusedPlanet = camera->getFocusedPlanet();
    
    // الحصول على المسافة عند التركيز من الكاميرا
    float focusDistance = camera->getFocusDistance();
    
    // الحصول على الوقت الحالي من النظام الشمسي
    double time = solarSystem->getTime();
    
    // ========================================================================
    // حالة 1: التركيز على الشمس (focusedPlanet == -1)
    // ========================================================================
    if (focusedPlanet == -1) {
        // نقطة النظر هي مركز النظام الشمسي (حيث توجد الشمس)
        lookX = 0.0f;
        lookY = 0.0f;
        lookZ = 0.0f;
        
        // الحصول على زاوية الدوران الأفقي من الكاميرا
        float angleY = camera->getAngleY();
        
        // إذا كان الدوران التلقائي مفعّلاً
        if (camera->getAutoRotate()) {
            // تحديث زاوية الدوران بناءً على الوقت (دوران تلقائي)
            angleY = (float)(time * 5.0);  // 5.0 = سرعة الدوران
        }
        
        // الحصول على زاوية الميل العمودي من الكاميرا
        float angleX = camera->getAngleX();
        
        // حساب موضع الكاميرا باستخدام الإحداثيات الكروية (Spherical Coordinates)
        // تحويل الزوايا من درجات إلى راديان
        camX = focusDistance * sin(angleY * M_PI_CONST / 180.0f) * cos(angleX * M_PI_CONST / 180.0f);
        camY = focusDistance * sin(angleX * M_PI_CONST / 180.0f);
        camZ = focusDistance * cos(angleY * M_PI_CONST / 180.0f) * cos(angleX * M_PI_CONST / 180.0f);
    }
    // ========================================================================
    // حالة 2: التركيز على كوكب معين (focusedPlanet >= 0)
    // ========================================================================
    else if (focusedPlanet >= 0 && focusedPlanet < solarSystem->getNumPlanets()) {
        // الحصول على مؤشر إلى الكوكب المُركز عليه
        Planet* planet = solarSystem->getPlanet(focusedPlanet);
        
        // الحصول على موضع الكوكب في الفضاء ثلاثي الأبعاد
        double lookXd, lookYd, lookZd;
        planet->getPosition(time, lookXd, lookYd, lookZd);
        
        // تحويل من double إلى float
        lookX = (float)lookXd;  // نقطة النظر = موضع الكوكب
        lookY = (float)lookYd;
        lookZ = (float)lookZd;
        
        // الحصول على زاوية الدوران الأفقي من الكاميرا
        float angleY = camera->getAngleY();
        
        // إذا كان الدوران التلقائي مفعّلاً
        if (camera->getAutoRotate()) {
            // تحديث زاوية الدوران بناءً على الوقت
            angleY = (float)(time * 5.0);
        }
        
        // الحصول على زاوية الميل العمودي من الكاميرا
        float angleX = camera->getAngleX();
        
        // حساب المسافة الإضافية من الكوكب (offset)
        // = حجم الكوكب × 3 + 2 وحدات (لإعطاء مسافة كافية)
        float offset = (float)(planet->getSize() * 3.0 + 2.0);
        
        // حساب موضع الكاميرا حول الكوكب باستخدام الإحداثيات الكروية
        camX = (float)(lookX + offset * sin(angleY * M_PI_CONST / 180.0f) * cos(angleX * M_PI_CONST / 180.0f));
        camY = (float)(lookY + offset * sin(angleX * M_PI_CONST / 180.0f));
        camZ = (float)(lookZ + offset * cos(angleY * M_PI_CONST / 180.0f) * cos(angleX * M_PI_CONST / 180.0f));
    }
    // ========================================================================
    // حالة 3: لا يوجد تركيز (Free Camera)
    // ========================================================================
    else {
        // نقطة النظر هي مركز النظام الشمسي
        lookX = 0.0f;
        lookY = 0.0f;
        lookZ = 0.0f;
        
        // الحصول على المسافة والزوايا من الكاميرا
        float distance = camera->getDistance();
        float angleY = camera->getAngleY();
        float angleX = camera->getAngleX();
        
        // حساب موضع الكاميرا باستخدام الإحداثيات الكروية
        camX = distance * sin(angleY * M_PI_CONST / 180.0f) * cos(angleX * M_PI_CONST / 180.0f);
        camY = distance * sin(angleX * M_PI_CONST / 180.0f);
        camZ = distance * cos(angleY * M_PI_CONST / 180.0f) * cos(angleX * M_PI_CONST / 180.0f);
    }
}

// ============================================================================
// دالة رسم واجهة المستخدم (HUD - Head-Up Display)
// ============================================================================
// هذه الدالة ترسم معلومات على الشاشة (الكوكب المُركز عليه، التعليمات)
// ============================================================================
void Renderer::renderHUD() {
    // إيقاف الإضاءة لرسم النص بوضوح
    glDisable(GL_LIGHTING);
    
    // حفظ إعدادات الإسقاط الحالية
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    
    // تعيين إسقاط متعامد ثنائي الأبعاد (Orthographic 2D)
    // للرسم على الشاشة مباشرة (بدون منظور)
    gluOrtho2D(0, 800, 0, 600);  // 800×600 = حجم النافذة
    
    // حفظ إعدادات النموذج الحالية
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    // تعيين لون النص (RGB: 0.9, 0.9, 0.9 = رمادي فاتح)
    glColor3f(0.9f, 0.9f, 0.9f);
    
    // تحديد موقع بدء رسم النص (10 بكسل من اليسار، 580 بكسل من الأسفل)
    glRasterPos2f(10, 580);
    
    // مصفوفة نصية لتخزين المعلومات
    char info[150];
    
    // الحصول على الكوكب المُركز عليه
    int focusedPlanet = camera->getFocusedPlanet();
    
    // بناء نص المعلومات بناءً على الحالة
    if (focusedPlanet == -1) {  // إذا كان التركيز على الشمس
        sprintf(info, "Focused: SUN | Distance: %.1f", camera->getFocusDistance());
    } else if (focusedPlanet >= 0 && focusedPlanet < solarSystem->getNumPlanets()) {  // إذا كان التركيز على كوكب
        Planet* planet = solarSystem->getPlanet(focusedPlanet);
        sprintf(info, "Focused: %s | Auto-Rotate: %s", 
               planet->getName(), camera->getAutoRotate() ? "ON" : "OFF");
    } else {  // إذا لم يكن هناك تركيز (Free Camera)
        sprintf(info, "Free Camera | Distance: %.1f", camera->getDistance());
    }
    
    // رسم النص حرفاً بحرف
    for (char* c = info; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);  // رسم الحرف الحالي
    }
    
    // تحديد موقع بدء رسم التعليمات (10 بكسل من اليسار، 560 بكسل من الأسفل)
    glRasterPos2f(10, 560);
    
    // نص التعليمات
    char controls[] = "Mouse: Rotate | W/S: Zoom | 0-9: Focus | A: Auto-Rotate | ESC: Menu | F11: Fullscreen";
    
    // رسم التعليمات حرفاً بحرف
    for (char* c = controls; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);  // رسم الحرف الحالي
    }
    
    // استعادة إعدادات النموذج السابقة
    glPopMatrix();
    
    // استعادة إعدادات الإسقاط السابقة
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    // العودة إلى مصفوفة النموذج
    glMatrixMode(GL_MODELVIEW);
    
    // إعادة تفعيل الإضاءة
    glEnable(GL_LIGHTING);
}
