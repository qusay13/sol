// تضمين مكتبة OpenGL للرسومات ثلاثية الأبعاد
#include <GL/glut.h>
// تضمين ملف الكلاس الرئيسي للتطبيق
#include "include/MainApp.h"

// النقطة الرئيسية لبدء تشغيل البرنامج
int main(int argc, char** argv) {
    // تهيئة مكتبة GLUT مع معاملات سطر الأوامر
    glutInit(&argc, argv);
    // تحديد وضع العرض: مزدوج Buffer + ألوان RGB + اختبار العمق
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    // تحديد حجم النافذة: 800 بكسل عرض × 600 بكسل ارتفاع
    glutInitWindowSize(800, 600);
    // تحديد موقع النافذة على الشاشة (100، 100)
    glutInitWindowPosition(100, 100);
    // إنشاء نافذة بعنوان "Solar System Simulation"
    glutCreateWindow("Solar System Simulation");
    
    // إنشاء كائن التطبيق الرئيسي
    MainApp app;
    // تهيئة إعدادات التطبيق والصوت والرسومات
    app.init();
    // تسجيل دوال Callback للتعامل مع الأحداث
    app.setupCallbacks();
    // بدء الحلقة الرئيسية للبرنامج (تبقى مستمرة حتى إغلاق النافذة)
    app.run();
    
    // إنهاء البرنامج بنجاح
    return 0;
}
