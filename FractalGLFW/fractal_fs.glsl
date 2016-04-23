
const int maxIt = 100;
const int r = 4;
const float speed = 0.5;

int Iteration(float x,float y, float cx, float cy, int maxIt, int r)
{
    int i = 0;
    float abs = sqrt(x * x + y * y);

     for(int j = 0; j < 100; j++)
    {
        float k = x;
        x = x*x - y*y + cx;
        y = 2.0 * y * k + cy;
        if(abs >= 2.0)
        {
            break;
        }
        i++;
        abs = sqrt(x * x + y * y);
    }
    return i;
}

void main()
{
    float zx = 0.0 - 0.78 * cos(iGlobalTime * speed);
    float zy = 0.0 + 0.78 * sin(iGlobalTime * speed);
    float minSide = min(iResolution.x, iResolution.y);
    float cx = float((gl_FragCoord.x - iResolution.x/2.0) * float(r)/minSide );
    float cy = float((gl_FragCoord.y - iResolution.y/2.0) *  float(r)/minSide);
    //int i = Iteration(zx, zy, cx, cy, maxIt, r);
    int i = Iteration(cx, cy, zx, zy, maxIt, r);

    if(i < maxIt)
    {
        float col =float(i)/float(maxIt/2);
        float rc = float(i)/150.0;
        gl_FragColor = vec4(rc, col, col, 1);
    }
    else
    {
        gl_FragColor = vec4(0, 0, 0, 1);
    }

}
